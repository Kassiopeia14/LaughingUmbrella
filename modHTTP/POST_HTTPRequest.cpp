#include "POST_HTTPRequest.h"

POST_HTTPRequest::POST_HTTPRequest()
{
}

POST_HTTPRequest::~POST_HTTPRequest()
{
}

std::string POST_HTTPRequest::send(std::wstring url, std::string data)
{
    DWORD data_len = data.length();
    
    std::wstring wsAdditionalHeaders(L"Content-Type: application/json\r\nContent-length: " + std::to_wstring(data_len) + L"\r\n");

    HINTERNET hSession = WinHttpOpen(
        NULL,
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS, 0);

    if (!hSession) throw;
    HINTERNET hConnect = WinHttpConnect(hSession, L"localhost", 7062, 0);

    if (!hConnect) throw;
    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"POST", url.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);

    if (!hRequest) throw;
    BOOL bResults = WinHttpSendRequest(hRequest, wsAdditionalHeaders.c_str(), -1, (LPVOID)data.c_str(), data_len, data_len, 0);
    
    if (!bResults) throw;
            
    bResults = WinHttpReceiveResponse(hRequest, NULL);

    if (!bResults) throw;
   
    DWORD dwSize;

    std::string response;

    do
    {
        dwSize = 0;
        if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) throw;

        char *pszOutBuffer = new char[dwSize + 1];
               
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