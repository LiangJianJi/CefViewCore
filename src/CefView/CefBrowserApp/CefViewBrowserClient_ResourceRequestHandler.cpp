#include <CefViewBrowserClient.h>

#pragma region stl_headers
#include <sstream>
#include <string>
#include <algorithm>
#pragma endregion

#include <Common/CefViewCoreLog.h>

CefRefPtr<CefResourceRequestHandler>
CefViewBrowserClient::GetResourceRequestHandler(CefRefPtr<CefBrowser> browser,
                                                CefRefPtr<CefFrame> frame,
                                                CefRefPtr<CefRequest> request,
                                                bool is_navigation,
                                                bool is_download,
                                                const CefString& request_initiator,
                                                bool& disable_default_handling)
{
  return this;
}

CefResourceRequestHandler::ReturnValue
CefViewBrowserClient::OnBeforeResourceLoad(CefRefPtr<CefBrowser> browser,
                                           CefRefPtr<CefFrame> frame,
                                           CefRefPtr<CefRequest> request,
#if CEF_VERSION_MAJOR > 91
                                           CefRefPtr<CefCallback> callback
#else
                                           CefRefPtr<CefRequestCallback> callback
#endif
)
{
  // url
  CefString currentUrl = request->GetURL();
  auto url = currentUrl.ToString();
  //std::string httpPrefix = "http";
  // origin
  std::string originString = "origin";
  std::string originStringUpper = "Origin";
  CefString currentOrigin = request->GetHeaderByName(originString);
  auto origin = currentOrigin.ToString();
  //logD("require origin - before: %s", origin.c_str());
  if (origin == "file://" /*&&
      url.size() >= httpPrefix.size() &&
      url.compare(0, httpPrefix.size(), httpPrefix) == 0*/) {
#if 0
    request->SetHeaderByName(originString, "", true);
#else
    // 获取请求头
    CefRequest::HeaderMap headers;
    request->GetHeaderMap(headers);
    //std::string tmpKeyString;
    //std::string tmpValueString;
    //for each (auto var in headers) {
    //  tmpKeyString = var.first.ToString();
    //  tmpValueString = var.second.ToString();
    //  logD("require headers: %s = %s", tmpKeyString.c_str(), tmpValueString.c_str());
    //}
    // 查找并移除 origin 的请求头字段
    auto it = headers.find(originString);
    if (it != headers.end()) {
      headers.erase(it);
    }
    auto itUpper = headers.find(originStringUpper);
    if (itUpper != headers.end()) {
      headers.erase(itUpper);
    }
    // 设置修改后的请求头
    request->SetHeaderMap(headers);
#endif
  }
  //logD("require origin - end: %s", origin.c_str());
  //logD("require resource: %s", url.c_str());
  return resource_manager_->OnBeforeResourceLoad(browser, frame, request, callback);
}

CefRefPtr<CefResourceHandler>
CefViewBrowserClient::GetResourceHandler(CefRefPtr<CefBrowser> browser,
                                         CefRefPtr<CefFrame> frame,
                                         CefRefPtr<CefRequest> request)
{
  return resource_manager_->GetResourceHandler(browser, frame, request);
}

void
CefViewBrowserClient::OnProtocolExecution(CefRefPtr<CefBrowser> browser,
                                          CefRefPtr<CefFrame> frame,
                                          CefRefPtr<CefRequest> request,
                                          bool& allow_os_execution)
{
}
