# MainContext
- Maincontext는 어플리케이션의 전반적인 흐름을 지니는 클래스
- MainContext::Get()을 통해 접근 가능
- MainContext는 전역 인스턴스로 존재하며, 이의 구현 클래스는 MainContextImpl

## 클래스 멤버 메서드
|접근제한자|키워드|반환|이름|설명|
|-------|--------|----------|-----------|-----------|
|public|static|MainContext*|Get()|자신의 전역 포인터 객체를 반환|
|public|virtual|string|GetConsoleLogPath()|콘솔 로그의 경로를 반환|
|public|virtual|string|GetDownloadPath()|파일의 전체 경로를 반환
|public|virtual|string|GetAppWorkingDirectory()|앱 작업 디렉토리 반환
|public|virtual|string|GetMainURL()|메인 어플리케이션 URL 반환
|public|virtual|cef_color_t|GetBackgroundColor()|배경색 반환
|public|virtual|bool|UseChromeRuntime()|크롬 런타임이 사용되면 true, 아니면 false
|public|virtual|bool|UseViews()|Views 프레임워크가 사용되면 true, 아니면 false
|public|virtual|bool|UseWindowlessRendering()|OSR이 사용되면 true, 아니면 false
|public|virtual|bool|TouchEventEnabled()|터치 이벤트가 사용되면 true, 아니면 false
|public|virtual|bool|PopulateSettings()|명령줄 인수에 따라 settings를 설정
|public|virtual|bool|PopulateBrowserSettings()|명령줄 인수에 따라 settings를 설정
|public|virtual|bool|PopulateOSRSettings()|명령줄 인수에 따라 settings를 설정
|public|virtual|RootWindowManager*|GetRootWindowManager()|루트창 매니저 반환
|protected|||MainContext()|생성자
|protected|virtual||~MainContext()|소멸자

# MainContextImpl : public MainContext
MainContext의 오버라이딩 메서드는 기재하지 않는다

## 클래스 멤버 메서드
|접근제한자|키워드|반환 타입|이름|설명|
|---|---|---|---|---|
|public|-|생성자|MainContextImpl()|-
|public|-|bool|Initialize()|CEF 및 메인 컨텍스트 관련된 것들 초기화, 해당 오브젝트를 생성한 동일한 스레드에서 호출돼야 함
|public|-|void|Shutdown()|CEF 및 메인 컨텍스트 관련된 것들 종료, 해당 오브젝트를 생성한 동일한 스레드에서 호출돼야 함
|private|friend|-|-|std::default_delete< MainContextImpl >
|private|-|소멸자|~MainContextImpl()|-
|private|const|bool|InValidState()|컨텍스트가 유효한 상태인지 반환, 초기화되고 종료되지 않았다면 true 아니면 false

## 클래스 멤버 변수
|타입|이름|설명|
|---|---|---|
|CefRefPtr< CefCommandLine >|command_line_|명령줄 정보
|const bool|terminate_when_all_windows_closed_|모든 창이 꺼지면 종료
|bool|initialized_|컨텍스트 상태 추적
|bool|shutdown_|컨텍스트 상태 추적
|string|main_url_|메인 URL
|cef_color_t|background_color_|배경색
|cef_color_t|browser_background_color_|브라우저 배경색
|bool|use_windowless_rendering|osr 설정
|int|windowless_frame_rate_|osr 일때 프레임률
|bool|use_chrome_runtime_|크롬 런타임 여부
|bool|use_views_|views 프레임워크 여부
|bool|touch_events_enabled_|터치 이벤트 활성화 여부
|unique_ptr< RootWindowManager >|root_window_manager_|루트창 매니저
|bool|external_begin_frame_enabled_|
|base::ThreadChecker|thread_checker_|유효한 스레드에서 호출됐는지에 대한 검사 변수

