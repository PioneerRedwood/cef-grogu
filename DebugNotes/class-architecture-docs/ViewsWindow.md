# ViewsMenuBar
- 상속 public: CefMenuButtonDelegate, CefMenuModelDelegate

## Delegate
|접근제한자|키워드|반환 타입|이름|설명|
|---|---|---|---|---|
|public|virtual|void|MenuBarExecuteCommand()|선택된 메뉴 명령을 실행
|protected|-|-|~Delegate()|소멸자

## CefButtonDelegate 오버라이딩 메서드
|접근제한자|키워드|반환 타입|이름|설명|
|---|---|---|---|---|
|protected|override|void|OnButtonPressed()|

## CefMenuButtonDelegate 오버라이딩 메서드
|접근제한자|키워드|반환 타입|이름|설명|
|---|---|---|---|---|
|protected|override|void|OnMenuButtonPressed()|

## CefMenuModleDelegate 오버라이딩 메서드
|접근제한자|키워드|반환 타입|이름|설명|
|---|---|---|---|---|
|proteced|override|void|ExecuteCommand()|
|proteced|override|void|MouseOutsideMenu()|
|proteced|override|void|UnhandledOpenSubmenu()|
|proteced|override|void|UnhandledCloseSubmenu()|
|proteced|override|void|MenuClosed()|

## 클래스 멤버 메서드
|접근제한자|키워드|반환 타입|이름|설명|
|---|---|---|---|---|
|public|-|-|ViewsMenuBar()|생성자
|public|read only(const)|bool|HasMenuId()|-
|public|-|CefRefPtr< CefPanel >|GetMenuPanel()|메뉴바를 나타내는 CefPanel 반환
|public|-|CefRefPtr< CefMenuModel >|CreateMenuModel()|새로운 메뉴 생성
|public|read only(const)|GetMenuModel()|특정 메뉴 반환
|public|-|void|SetMenuFocusable()|메뉴에 포커스를 설정하거나 제거. ViewsWindow::OnKeyEvent에서 설정. ALT 키 누르면 포커스 활성화
|public|-|bool|OnKeyEvent()|ViewsWindow::OnKeyEvent 이벤트
|public|-|void|Reset()|메뉴바 상태 초기 상태로 설정(리셋)
|private|-|void|EnsureMenuPanel()|이미 존재하지 않으면 메뉴 패널 생성
|private|-|int|GetActiveMenuId()|활성화인 메뉴 ID 반환, 없으면 -1 반환
|private|-|void|TriggerNextMenu()|현재 활성화 메뉴에서 특정 메뉴 트리거
|private|-|void|TriggerMenuButon()|특정 메뉴 버튼 트리거

## 클래스 멤버 변수
|접근제한자|키워드|타입|이름|설명|
|---|---|---|---|---|
|private|-|Delegate*|delegate_|해당 객체에서 소유하지 않음
|private|const|int|id_start_|-
|private|-|int|id_next_|-
|private|-|CefRefPtr< CefPanel >|panel_|-
|private|-|vector< CefRefPtr < CefMenuModel > >|models_|-
|private|-|bool|last_nav_with_keyboard_|-
|private|-|MnenomicMap(map< char16, int >)|mnemonics_|-

# ViewsWindow

- 지금은 사용 안하는 것으로 판명