
# RootWindow
브라우저의 최상위(루트) 네이티브 창을 나타낸다.

|접근제한자|키워드|반환 타입|이름|설명|
|---|---|---|---|---|
|public|static|scoped_refptr< RootWindow >|Create()|새로운 루트창 오브젝트 생성
|public|static|scoped_refptr< RootWindow >|GetForBrowser()|브라우저 ID와 관련된 루트창 반환
|public|virtual|void|Init()|일반 창으로 초기화
|public|virtual|void|InitAsPopup()|팝업 창으로 초기화
|public|virtual|void|Show()|창 보이기
|public|virtual|void|Hide()|창 숨기기
|public|virtual|void|SetBounds()|화면 좌표에 맞게 창 위치 설정
|public|virtual|void|Close()|창 닫기
|public|virtual|void|SetDeviceScaleFactor()|장비 스케일 요소 설정, OSR 일때만 사용됨
|public|virtual|float|GetDeviceScaleFactor()|장비 스케일 요소 반환
|public|virtual|CefRefPtr< CefBrowser >|GetBrowser()|현재 창을 포함하는 브라우저 반환
|public|virtual|ClientWindowHandle|GetWindowHandle()|현재 창의 네이티브 핸들을 반환
|public|virtual|bool|OSR을 사용하는 창이면 true, 아니면 false
|public|virtual|bool|확장 앱을 호스팅하는 창이라면 true, 아니면 false
|public|virtual|void|OnExtensionChanged()|로드된 확장이 변경되면 호출

## RootWindowConfig
- 루트창이 어떻게 생성될 지에 대한 설정 구조체

|타입|이름|설명|
|--|--|--|
|-|RootWindowConfig()|생성자|
|bool|always_on_top|항상 위면 true, 아니면 false|
|bool|with_controls|제어 버튼 활성화 돼있으면 true, 아니면 false|
|bool|with_osr|osr 사용하면 true, 아니면 false|
|bool|with_extension|확장 앱을 호스팅하면 true, 아니면 false|
|bool|initially_hidden|숨긴 상태로 초기화하면 true, 아니면 false|
|CefRect|bounds|창의 위치|
|CefRect|source_bounds|창이 생성될 UI 요소 위치|
|CefRefPtr< CefWindow >|parent_window|views 프레임워크에서만 사용되는 부모 윈도우|
|base::OnceClosure||창이 닫힐 때 실행되는 콜백|
|string|url|처음 로드할 URL

## RootWindow::Delegate
- 내부 클래스

|접근제한자|키워드|반환 타입|이름|설명|
|---|---|---|---|---|
|public|virtual|CefRefPtr < CefRequestContext >|GetRequestContext()|브라우저에 있는 CefRequestContext를 생성하는데 사용
|public|virtual|scoped_refptr< ImageCache >|GetImageCache()|이미지 캐시 반환
|public|virtual|void|OnTest()|테스트 실행되면 호출, resource.h에 등록된 test_id 참고
|public|virtual|void|OnExit()|어플리케이션을 종료하면 호출
|public|virtual|void|OnRootWindowDestroyed()|루트창이 파괴되면 호출
|public|virtual|void|OnRootWindowActivated()|루트창이 활성화되면 호출
|public|virtual|void|OnBrowserCreated()|루트창에 브라우저가 생성되면 호출
|public|virtual|void|CreateExtensionWindow()|확장에 대한 창을 생성
|protected|virtual|-|~Delegate()|소멸자



# RootWindowManager
- 루트창 인스턴스를 생성하고 관리하는데 사용된다.
- RootWindow의 내부 클래스인 RootWindow::Delegate를 구현한다, 오버라이딩 메서드는 기재하지 않는다.
## 메서드
|접근제한자|키워드|반환 타입|이름|설명|
|---|---|---|---|---|
|public|explicit|생성자|RootWindowManager()|생성자
|public|-|scoped_ptr< RootWindow >|CreateRootWindow()|새로운 최상위 네이티브 창을 생성
|public|-|scoped_ptr< RootWindow >|CreateRootWindowAsPopup()|새로운 네이티브 팝업 창을 생성
|public|-|scoped_ptr< RootWindow >|CreateRootWindowAsExtension()|확장을 호스팅하는 새로운 최상위 네이티브 창을 생성
|public|-|bool|HasRootWindowAsExtension()|현존하는 확장을 호스팅하는 창이 있으면 true, 없으면 false
|public|read only(const)|scoped_ptr< RootWindow >|GetWindowForBrowser()|브라우저 ID의 루트창 반환
|public|read only(const)|scoped_ptr< RootWindow >|GetActiveForBrowser()|현재 활성화인 루트창 반환
|public|-|void|CloseAllWindows()|모든 현존하는 창 닫기
|public|-|void|AddExtension()|로드된 확장을 관리
|public|read only(const)|bool|request_context_per_browser()|-
|private|-|-|~RootWindowManager()|소멸자
|private|-|void|OnRootWindowCreated()|루트창 생성 시 호출
|private|-|void|NotifyExtensionsChanged()|확장 변경 통지
|private|-|void|CleanupOnUIThread()|-

- RootWindow::Delegate 오버라이드한 메서드는 위를 참고

## 변수
|타입|이름|설명|
|--|--|--|
|const bool|terminate_when_all_windows_closed_|종료 시 모든 창 닫기
|bool|request_context_per_browser_|-
|bool|request_context_shared_cache_|-
|RootWindowSet|root_windows_|-
|scoped_ptr< RootWindow >|active_root_window_|-
|mutable base::Lock|active_browser_lock_|활성화된 포그라운드 브라우저에 대한 락
|CefRefPtr< CefBrowser >|active_browser_|활성화된 포그라운드 브라우저
|std::unique_lock< TempWindow >|temp_window_|팝업 브라우저의 임시 부모로 사용되는 싱글톤 창
|CefRefPtr< CefRequestContext >|shared_request_context_|-
|ExtensionSet|extensions_|로드된 확장들, 메인 스레드에서만 접근
|scoped_ptr< ImageCache >|image_cache_|이미지 캐시