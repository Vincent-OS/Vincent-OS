/*
 *  Notepad (text.c)
 *
 *  Copyright 1998,99 Marcel Baur <mbaur@g26.ethz.ch>
 *  Copyright 2002 Sylvain Petreolle <spetreolle@yahoo.fr>
 *  Copyright 2002 Andriy Palamarchuk
 *  Copyright 2019 Katayama Hirofumi MZ <katayama.hirofumi.mz@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "notepad.h"

static BOOL Append(LPWSTR *ppszText, DWORD *pdwTextLen, LPCWSTR pszAppendText, DWORD dwAppendLen)
{
    LPWSTR pszNewText;

    if (dwAppendLen > 0)
    {
        if (*ppszText)
        {
            pszNewText = (LPWSTR) HeapReAlloc(GetProcessHeap(), 0, *ppszText, (*pdwTextLen + dwAppendLen) * sizeof(WCHAR));
        }
        else
        {
            pszNewText = (LPWSTR) HeapAlloc(GetProcessHeap(), 0, dwAppendLen * sizeof(WCHAR));
        }

        if (!pszNewText)
            return FALSE;

        memcpy(pszNewText + *pdwTextLen, pszAppendText, dwAppendLen * sizeof(WCHAR));
        *ppszText = pszNewText;
        *pdwTextLen += dwAppendLen;
    }
    return TRUE;
}

BOOL IsTextNonZeroASCII(const void *pText, DWORD dwSize)
{
    const signed char *pBytes = pText;
    while (dwSize-- > 0)
    {
        if (*pBytes <= 0)
            return FALSE;

        ++pBytes;
    }
    return TRUE;
}

ENCODING AnalyzeEncoding(const char *pBytes, DWORD dwSize)
{
    INT flags = IS_TEXT_UNICODE_STATISTICS;

    if (dwSize <= 1)
        return ENCODING_ANSI;

    if (IsTextNonZeroASCII(pBytes, dwSize))
    {
        return ENCODING_ANSI;
    }

    if (IsTextUnicode(pBytes, dwSize, &flags))
    {
        return ENCODING_UTF16LE;
    }

    if ((flags & IS_TEXT_UNICODE_REVERSE_MASK) && !(flags & IS_TEXT_UNICODE_ILLEGAL_CHARS))
    {
        return ENCODING_UTF16BE;
    }

    /* is it UTF-8? */
    if (MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, pBytes, dwSize, NULL, 0))
    {
        return ENCODING_UTF8;
    }

    return ENCODING_ANSI;
}

BOOL
ReadText(HANDLE hFile, LPWSTR *ppszText, DWORD *pdwTextLen, ENCODING *pencFile, int *piEoln)
{
    DWORD dwSize;
    LPBYTE pBytes = NULL;
    LPWSTR pszText;
    LPWSTR pszAllocText = NULL;
    DWORD dwPos, i;
    DWORD dwCharCount;
    BOOL bSuccess = FALSE;
    BYTE b = 0;
    ENCODING encFile = ENCODING_ANSI;
    int iCodePage = 0;
    WCHAR szCrlf[2] = {'\r', '\n'};
    DWORD adwEolnCount[3] = {0, 0, 0};

    *ppszText = NULL;
    *pdwTextLen = 0;

    dwSize = GetFileSize(hFile, NULL);
    if (dwSize == INVALID_FILE_SIZE)
        goto done;

    pBytes = HeapAlloc(GetProcessHeap(), 0, dwSize + 2);
    if (!pBytes)
        goto done;

    if (!ReadFile(hFile, pBytes, dwSize, &dwSize, NULL))
        goto done;
    dwPos = 0;

    /* Make sure that there is a NUL character at the end, in any encoding */
    pBytes[dwSize + 0] = '\0';
    pBytes[dwSize + 1] = '\0';

    /* Look for Byte Order Marks */
    if ((dwSize >= 2) && (pBytes[0] == 0xFF) && (pBytes[1] == 0xFE))
    {
        encFile = ENCODING_UTF16LE;
        dwPos += 2;
    }
    else if ((dwSize >= 2) && (pBytes[0] == 0xFE) && (pBytes[1] == 0xFF))
    {
        encFile = ENCODING_UTF16BE;
        dwPos += 2;
    }
    else if ((dwSize >= 3) && (pBytes[0] == 0xEF) && (pBytes[1] == 0xBB) && (pBytes[2] == 0xBF))
    {
        encFile = ENCODING_UTF8BOM;
        dwPos += 3;
    }
    else
    {
        encFile = AnalyzeEncoding((const char *)pBytes, dwSize);
    }

    switch(encFile)
    {
    case ENCODING_UTF16BE:
        for (i = dwPos; i < dwSize-1; i += 2)
        {
            b = pBytes[i+0];
            pBytes[i+0] = pBytes[i+1];
            pBytes[i+1] = b;
        }
        /* fall through */

    case ENCODING_UTF16LE:
        pszText = (LPWSTR) &pBytes[dwPos];
        dwCharCount = (dwSize - dwPos) / sizeof(WCHAR);
        break;

    case ENCODING_ANSI:
    case ENCODING_UTF8:
    case ENCODING_UTF8BOM:
        if (encFile == ENCODING_UTF8 || encFile == ENCODING_UTF8BOM)
            iCodePage = CP_UTF8;
        else
            iCodePage = CP_ACP;

        if ((dwSize - dwPos) > 0)
        {
            dwCharCount = MultiByteToWideChar(iCodePage, 0, (LPCSTR)&pBytes[dwPos], dwSize - dwPos, NULL, 0);
            if (dwCharCount == 0)
                goto done;
        }
        else
        {
            /* special case for files with no characters (other than BOMs) */
            dwCharCount = 0;
        }

        pszAllocText = (LPWSTR) HeapAlloc(GetProcessHeap(), 0, (dwCharCount + 1) * sizeof(WCHAR));
        if (!pszAllocText)
            goto done;

        if ((dwSize - dwPos) > 0)
        {
            if (!MultiByteToWideChar(iCodePage, 0, (LPCSTR)&pBytes[dwPos], dwSize - dwPos, pszAllocText, dwCharCount))
                goto done;
        }

        pszAllocText[dwCharCount] = '\0';
        pszText = pszAllocText;
        break;
    DEFAULT_UNREACHABLE;
    }

    dwPos = 0;
    for (i = 0; i < dwCharCount; i++)
    {
        switch(pszText[i])
        {
        case '\r':
            if ((i < dwCharCount-1) && (pszText[i+1] == '\n'))
            {
                i++;
                adwEolnCount[EOLN_CRLF]++;
                break;
            }
            /* fall through */

        case '\n':
            if (!Append(ppszText, pdwTextLen, &pszText[dwPos], i - dwPos))
                return FALSE;
            if (!Append(ppszText, pdwTextLen, szCrlf, ARRAY_SIZE(szCrlf)))
                return FALSE;
            dwPos = i + 1;

            if (pszText[i] == '\r')
                adwEolnCount[EOLN_CR]++;
            else
                adwEolnCount[EOLN_LF]++;
            break;

        case '\0':
            pszText[i] = ' ';
            break;
        }
    }

    if (!*ppszText && (pszText == pszAllocText))
    {
        /* special case; don't need to reallocate */
        *ppszText = pszAllocText;
        *pdwTextLen = dwCharCount;
        pszAllocText = NULL;
    }
    else
    {
        /* append last remaining text */
        if (!Append(ppszText, pdwTextLen, &pszText[dwPos], i - dwPos + 1))
            return FALSE;
    }

    /* chose which eoln to use */
    *piEoln = EOLN_CRLF;
    if (adwEolnCount[EOLN_LF] > adwEolnCount[*piEoln])
        *piEoln = EOLN_LF;
    if (adwEolnCount[EOLN_CR] > adwEolnCount[*piEoln])
        *piEoln = EOLN_CR;
    *pencFile = encFile;

    bSuccess = TRUE;

done:
    if (pBytes)
        HeapFree(GetProcessHeap(), 0, pBytes);
    if (pszAllocText)
        HeapFree(GetProcessHeap(), 0, pszAllocText);

    if (!bSuccess && *ppszText)
    {
        HeapFree(GetProcessHeap(), 0, *ppszText);
        *ppszText = NULL;
        *pdwTextLen = 0;
    }
    return bSuccess;
}

static BOOL WriteEncodedText(HANDLE hFile, LPCWSTR pszText, DWORD dwTextLen, ENCODING encFile)
{
    LPBYTE pBytes = NULL;
    LPBYTE pAllocBuffer = NULL;
    DWORD dwPos = 0;
    DWORD dwByteCount;
    BYTE buffer[1024];
    UINT iCodePage = 0;
    DWORD dwDummy, i;
    BOOL bSuccess = FALSE;
    int iBufferSize, iRequiredBytes;
    BYTE b;

    while(dwPos < dwTextLen)
    {
        switch(encFile)
        {
            case ENCODING_UTF16LE:
                pBytes = (LPBYTE) &pszText[dwPos];
                dwByteCount = (dwTextLen - dwPos) * sizeof(WCHAR);
                dwPos = dwTextLen;
                break;

            case ENCODING_UTF16BE:
                dwByteCount = (dwTextLen - dwPos) * sizeof(WCHAR);
                if (dwByteCount > sizeof(buffer))
                    dwByteCount = sizeof(buffer);

                memcpy(buffer, &pszText[dwPos], dwByteCount);
                for (i = 0; i < dwByteCount; i += 2)
                {
                    b = buffer[i+0];
                    buffer[i+0] = buffer[i+1];
                    buffer[i+1] = b;
                }
                pBytes = (LPBYTE) &buffer[dwPos];
                dwPos += dwByteCount / sizeof(WCHAR);
                break;

            case ENCODING_ANSI:
            case ENCODING_UTF8:
            case ENCODING_UTF8BOM:
                if (encFile == ENCODING_UTF8 || encFile == ENCODING_UTF8BOM)
                    iCodePage = CP_UTF8;
                else
                    iCodePage = CP_ACP;

                iRequiredBytes = WideCharToMultiByte(iCodePage, 0, &pszText[dwPos], dwTextLen - dwPos, NULL, 0, NULL, NULL);
                if (iRequiredBytes <= 0)
                {
                    goto done;
                }
                else if (iRequiredBytes < sizeof(buffer))
                {
                    pBytes = buffer;
                    iBufferSize = sizeof(buffer);
                }
                else
                {
                    pAllocBuffer = (LPBYTE) HeapAlloc(GetProcessHeap(), 0, iRequiredBytes);
                    if (!pAllocBuffer)
                        return FALSE;
                    pBytes = pAllocBuffer;
                    iBufferSize = iRequiredBytes;
                }

                dwByteCount = WideCharToMultiByte(iCodePage, 0, &pszText[dwPos], dwTextLen - dwPos, (LPSTR) pBytes, iBufferSize, NULL, NULL);
                if (!dwByteCount)
                    goto done;

                dwPos = dwTextLen;
                break;

            default:
                goto done;
        }

        if (!WriteFile(hFile, pBytes, dwByteCount, &dwDummy, NULL))
            goto done;

        /* free the buffer, if we have allocated one */
        if (pAllocBuffer)
        {
            HeapFree(GetProcessHeap(), 0, pAllocBuffer);
            pAllocBuffer = NULL;
        }
    }
    bSuccess = TRUE;

done:
    if (pAllocBuffer)
        HeapFree(GetProcessHeap(), 0, pAllocBuffer);
    return bSuccess;
}

BOOL WriteText(HANDLE hFile, LPCWSTR pszText, DWORD dwTextLen, ENCODING encFile, int iEoln)
{
    WCHAR wcBom;
    LPCWSTR pszLF = L"\n";
    DWORD dwPos, dwNext;

    /* Write the proper byte order marks if not ANSI or UTF-8 without BOM */
    if (encFile != ENCODING_ANSI && encFile != ENCODING_UTF8)
    {
        wcBom = 0xFEFF;
        if (!WriteEncodedText(hFile, &wcBom, 1, encFile))
            return FALSE;
    }

    dwPos = 0;

    /* pszText eoln are always \r\n */

    do
    {
        /* Find the next eoln */
        dwNext = dwPos;
        while(dwNext < dwTextLen)
        {
            if (pszText[dwNext] == '\r' && pszText[dwNext + 1] == '\n')
                break;
            dwNext++;
        }

        if (dwNext != dwTextLen)
        {
            switch (iEoln)
            {
            case EOLN_LF:
                /* Write text (without eoln) */
                if (!WriteEncodedText(hFile, &pszText[dwPos], dwNext - dwPos, encFile))
                    return FALSE;
                /* Write eoln */
                if (!WriteEncodedText(hFile, pszLF, 1, encFile))
                    return FALSE;
                break;
            case EOLN_CR:
                /* Write text (including \r as eoln) */
                if (!WriteEncodedText(hFile, &pszText[dwPos], dwNext - dwPos + 1, encFile))
                    return FALSE;
                break;
            case EOLN_CRLF:
                /* Write text (including \r\n as eoln) */
                if (!WriteEncodedText(hFile, &pszText[dwPos], dwNext - dwPos + 2, encFile))
                    return FALSE;
                break;
            default:
                return FALSE;
            }
        }
        else
        {
            /* Write text (without eoln, since this is the end of the file) */
            if (!WriteEncodedText(hFile, &pszText[dwPos], dwNext - dwPos, encFile))
                return FALSE;
        }

        /* Skip \r\n */
        dwPos = dwNext + 2;
    }
    while (dwPos < dwTextLen);

    return TRUE;
}
