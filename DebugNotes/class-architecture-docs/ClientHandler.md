
# CefClient : public virtual CefBaseRefCounted
- path: include\cef_client.h

## 메서드
|접근제한자|키워드|반환 타입|이름|설명|
|---|---|---|---|---|
|public|virtual|CefRefPtr< CefAudioHandler >|GetAudioHandler()|오디오 렌더링 이벤트 핸들러
|public|virtual|CefRefPtr< CefContextMenuHandler >|GetContextMenuHandler()|컨텍스트 메뉴 핸들러
|public|virtual|CefRefPtr< CefDialogHandler >|GetDialogHandler()|다이얼로그 핸들러
|public|virtual|CefRefPtr< CefDisplayHandler >|GetDisplayHandler()|디스플레이 상태 이벤트 핸들러
|public|virtual|CefRefPtr< CefDownloadHandler >|GetDownloadHandler()|다운로드 이벤트 핸들러
|public|virtual|CefRefPtr< CefDragHandler >|GetDragHandler()|드래그 이벤트 핸들러
|public|virtual|CefRefPtr< CefFindHandler >|GetFindHandler()|찾기 결과 이벤트 핸들러
|public|virtual|CefRefPtr< CefFocusHandler >|GetFocusHandler()|포커스 이벤트 핸들러
|public|virtual|CefRefPtr< CefFrameHandler >|GetFrameHandler()|CefFrame 생명주기와 연관된 이벤트  핸들러
|public|virtual|CefRefPtr< CefJSDialogHandler >|GetJSDialogHandler()|JavaScript 다이얼로그 핸들러
|public|virtual|CefRefPtr< CefKeyboardHandler >|GetKeyboardHandler()|키보드 이벤트 핸들러
|public|virtual|CefRefPtr< CefLifeSpanHandler >|GetLifeSpanHandler()|브라우저 생명 주기 이벤트 핸들러
|public|virtual|CefRefPtr< CefLoadHandler >|GetLoadHandler()|브라우저 로드 상태 이벤트 핸들러
|public|virtual|CefRefPtr< CefPrintHandler >|GetPrintHandler()|리눅스에서 프린트 이벤트 핸들러
|public|virtual|CefRefPtr< CefRenderHandler >|GetRender Handler()|osr 렌더링 이벤트 핸들러
|public|virtual|CefRefPtr< CefRequestHandler >|GetRequest Handler()|브라우저 요청 이벤트 핸들러
|public|virtual|bool|OnProcessMessageReceived()|다른 프로세스로부터 메시지 수신 시 호출

- 해당 클래스를 상속하면 클래스 가상 멤버 메서드로 존재하는 핸들러 반환의 유형에 맞는 클래스 역시 상속해야 한다
- 만약에 CefClient::GetContextMenuHandler()로 컨텍스트 메뉴 핸들러를 사용하려면 CefClient를 상속하는 클래스 역시 CefContextMenuHandler 클래스를 상속해야 메서드 호출 시 유효한 값이 반환된다.(not a nullptr)

# ClientHandler
- 프로그램 기능의 대부분을 구현하는 클래스
- CefClient 자체와 그 안에 정의된 핸들러 클래스를 상속해 구현한다
- 내부 클래스인 Delegate는 BrowserWindow의 부모 클래스이며, 구현할 인터페이스를 제공한다

## 상속 클래스
- CefClient
- CefContextMenuHandler
- CefDisplayHandler
- CefLifeSpanHandler
- CefLoadHandler
- CefRequestHandler
- CefResouceRequestHandler
- 상속된 모든 핸들러 클래스의 메서드를 오버라이딩


## 내부 클래스 Delegate
|접근제한자|키워드|반환 타입|이름|설명|
|---|---|---|---|---|
|public|virtual|void|OnBrowserCreated()|브라우저 생성 시
|public|virtual|void|OnBrowserClosing()|브라우저가 닫힐 때
|public|virtual|void|OnBrowserClosed()|브라우저를 닫을 때
|public|virtual|void|OnSetAddress()|창 URL 설정 시
|public|virtual|void|OnSetTitle()|창 제목 설정 시
|public|virtual|void|OnSetFavicon()|Favicon 이미지 설정 시
|public|virtual|void|OnSetFullScreen()|전체화면 설정 시
|public|virtual|void|OnAutoResize()|컨텐츠 자동 크기 조절 시
|public|virtual|void|OnSetLoadingState()|로딩 상태 설정 시
|public|virtual|void|OnSetDraggableRegions()|드래그 가능한 구역 설정 시
|public|virtual|void|OnTakeFocus()|이후/이전 제어에 포커스 시 호출
|public|virtual|void|OnBeforeContextMenu()|컨텍스트 메뉴가 출력되기 전에 UI 스레드에서 호출
|protected|-|-|~Delegate()|-

## ClientHandler 메서드

|접근제한자|키워드|반환 타입|이름|설명|
|---|---|---|---|---|
|public|-|-|ClientHandler()|생성자
|public|-|void|DetachDelegate()|This object may outlive the Delegate object so it's necessary for the Delegate to detach itself before destruction.
|public|read only(const)|int|GetBrowserCount()|해당 핸들러를 사용하는 브라우저의 수 반환
|public|-|void|ShowDevTools()|DevTools 팝업 창 보이기
|public|-|void|CloseDevTools()|DevTools 팝업 창 닫기
|public|-|void|HasSSLInformation()|현 사이트가 SSL 정보가 사용 가능한지 테스트
|public|-|void|ShowSSLInformation()|현 사이트의 SSL 정보 출력
|public|-|void|SetStringResource()|문자열 리소스를 StringResourceProvider를 통해 설정
|public|read only(const)|Delegate*|delegate()|델리게이트 반환
|public|read only(const)|string|startup_url()|시작 URL 반환
|public|read only(const)|bool|is_osr()|osr 사용하는지 반환
|public|read only(const)|bool|download_favicon_images()|favicon 이미지를 다운해야 하면 true, 아니면 false
|public|-|void|set_download_favicon_images()|favicon 이미지를 다운해야 하는지 설정
|private|-|bool|CreatePopupWindow()|명시된 정보를 사용하는 새로운 팝업 창을 생성
|private|-|void|NotifyBrowserCreated|-
|private|-|void|NotifyBrowserClosing|-
|private|-|void|NotifyBrowserClosed|-
|private|-|void|NotifyAddress|-
|private|-|void|NotifyTitle|-
|private|-|void|NotifyFavicon|-
|private|-|void|NotifyFullscreen|-
|private|-|void|NotifyAutoResize|-
|private|-|void|NotifyLoadingState|-
|private|-|void|NotifyDraggableRegions|-
|private|-|void|NotifyTakeFocus|-
|private|-|void|BuildTestMenu|테스트 메뉴 생성
|private|-|void|ExecuteTestMenu|테스트 메뉴 실행
|private|-|void|SetOfflineState|-


## ClientHandler 변수
|타입|이름|설명|
|--|--|--|
|const bool|is_osr_|osr 사용
|const string|startup_url_|시작 URL
|bool|mouse_cursor_change_disabled|마우스 커서 변경이 비활성화인지
|bool|offline_|브라우저가 현재 오프러인인지
|bool|download_favicon_images_|Favicon 이미지 다운해야 하는지
|CefRefPtr< CefMessageRouterBrowserSide >|message_router_|쿼리 라우팅하는 브라우저 핸들
|CefRefPtr< CefResourceManager >|resource_manager_|리소스 매니저
|test_runner::StringResourceMap|string_resource_map_|StringResourceProvider와 함께 문자열 리소스를 관리하는데 사용
|Delegate*|delegate_|델리게이트
|TestMenuState|test_menu_state_|테스트 메뉴 선택 구조체
|int|browser_count_|해당 핸들러를 사용하는 브라우저 수
|const string|console_log_file_|콘솔 로그 상태
|bool|first_console_message_|-
|bool|focus_on_editable_field_|-
|bool|initial_navigation_|브라우저 생성 뒤 초기 네비게이션일 경우 true
|MessageHandlerSet|message_handler_set_|메시지 핸들러 모음, 메시지 라우터를 통해 등록됨

## CefClient override 메서드
- CefClient 메서드 참고

## CefContextMenuHandler override 메서드
|접근제한자|키워드|반환 타입|이름|설명|
|---|---|---|---|---|
|public|override|void|OnBeforeContextMenu()|-
|public|override|void|OnContextMenuCommand()|-

## CefDisplayHandler override 메서드
|접근제한자|키워드|반환 타입|이름|설명|
|---|---|---|---|---|
|public|override|void|OnAddressChange()|-
|public|override|void|OnTitleChange()|-
|public|override|void|OnFaviconURLChange()|-
|public|override|void|OnConsoleMessage()|-
|public|override|void|OnAutoResize()|-
|public|override|void|OnCursorChange()|-

## CefLifeSpanHandler override 메서드
|접근제한자|키워드|반환 타입|이름|설명|
|---|---|---|---|---|
|public|override|void|OnBeforePopup()|-
|public|override|void|OnAfterCreated()|-
|public|override|void|DoClose()|-
|public|override|void|OnBeforeClose()|-

## CefLoadHandler override 메서드
|접근제한자|키워드|반환 타입|이름|설명|
|---|---|---|---|---|
|public|override|void|OnLoadingStateChange()|-
|public|override|void|OnLoadError()|-

## CefRequestHandler override 메서드
|접근제한자|키워드|반환 타입|이름|설명|
|---|---|---|---|---|
|public|override|void|OnBeforeBrowe()|-
|public|override|void|OnOpenURLFromTab()|-
|public|override|CefRefPtr< CefResourceRequestHandler >|GetResourceRequestHandler()|-
|public|override|bool|GetAuthCredentials()|-
|public|override|bool|OnQuotaRequest()|-
|public|override|bool|OnCertificateError()|-
|public|override|bool|OnSelectClientCertificate()|-
|public|override|void|OnRenderProcessTerminated()|-
|public|override|void|OnDocumentAvailableInMainFrame()|-

## CefResourceRequestHandler override 메서드
|접근제한자|키워드|반환 타입|이름|설명|
|---|---|---|---|---|
|public|override|cef_return_value_t|OnBeforeResourceLoad()|-
|public|override|CefRefPtr< CefResourceHandler >|GetResourceHandler()|-
|public|override|CefRefPtr< CefResponseFilter >|GetResourceResponseFilter()|-
|public|override|void|OnProtocolExecution()|-
