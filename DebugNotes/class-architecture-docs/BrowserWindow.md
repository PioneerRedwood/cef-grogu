# BrowserWindow
- 단일 브라우저 인스턴스의 기본 자식 창을 나타낸다
- ClientHandler::Delegate를 상속받음, 오버라이딩 메서드는 생략

## Delegate
|접근제한자|키워드|반환 타입|이름|설명|
|---|---|---|---|---|
|public|virtual|void|OnBrowserCreated()|-
|public|virtual|void|OnBrowserWindowClosing|-
|public|virtual|void|OnBrowserWindowDestroyed|-
|public|virtual|void|OnSetAddress|-
|public|virtual|void|OnSetTitle|-
|public|virtual|void|OnSetFullscreen|-
|public|virtual|void|OnAutoResize|-
|public|virtual|void|OnSetLoadingState|-
|public|virtual|void|OnSetDraggableRegions|-
|public|virtual|-|~Delegate()|소멸자


## 클래스 멤버 메서드
|접근제한자|키워드|반환 타입|이름|설명|
|---|---|---|---|---|
|public|virtual|void|CreateBrowser()|-
|public|virtual|void|GetPopupConfig()|-
|public|virtual|void|ShowPopup()|-
|public|virtual|void|Show()|-
|public|virtual|void|Hide()|-
|public|virtual|void|SetBounds()|-
|public|virtual|void|SetFocus()|-
|public|virtual|void|SetDeviceScaleFactor()|-
|public|virtual|float|GetDeviceScaleFactor()|-
|public|virtual & read only(const)|ClientWindowHandle|GetWindowHandle()|-
|public|read only(const)|CefRefPtr< CefBrowser >|GetBrowser()|-
|public|read only(const)|bool|IsClosing()|-
|protected|explicit|-|BrowserWindow()|생성자

- ClientHandler::Delegate 오버라이딩 메서드는 생략

## 클래스 멤버 변수
|접근제한자|타입|이름|설명|
|---|---|---|---|
|protected|Delegate*|delegate_|-
|protected|CefRefPtr< CefBrowser >|browser_|-
|protected|CefRefPtr< ClientHandler >|client_handler_|-
|protected|bool|is_closing_|-

# BrowserWindowWin
- BrowserWindow를 상속받는다
- BrowserWindow 오버라이딩 메서드는 생략
- 창이 있는 단일 브라우저 인스턴스를 호스팅하는 기본 자식 창을 나타낸다

|접근제한자|키워드|반환 타입|이름|설명|
|---|---|---|---|---|
|public|-|-|BrowserWindowWin|생성자