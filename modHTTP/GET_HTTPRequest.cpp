#include "GET_HTTPRequest.h"

GET_HTTPRequest::GET_HTTPRequest()
{
}

GET_HTTPRequest::~GET_HTTPRequest()
{
}

std::string GET_HTTPRequest::get(std::wstring url)
{
    HINTERNET hSession = WinHttpOpen(
        NULL,
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS, 0);

    if (!hSession) throw;
    HINTERNET hConnect = WinHttpConnect(hSession, L"localhost", 7062, 0);

    if (!hConnect) throw;
    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", url.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);

    if (!hRequest) throw;
    BOOL bResults = WinHttpSendRequest(hRequest,
        WINHTTP_NO_ADDITIONAL_HEADERS, 0,
        WINHTTP_NO_REQUEST_DATA, 0,
        0, 0);

    if (!bResults) throw;

    bResults = WinHttpReceiveResponse(hRequest, NULL);

    if (!bResults) throw;

    DWORD dwSize;

    std::string response;

    do
    {
        dwSize = 0;
        if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) throw;

        char* pszOutBuffer = new char[dwSize + 1];

        ZeroMemory(pszOutBuffer, dwSize + 1);

        DWORD dwDownloaded = 0;
        if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded)) throw;

        response = response + std::string(pszOutBuffer);

        delete[] pszOutBuffer;

    } while (dwSize > 0);

    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);

    return response;
}
