# cef-grogu
cefclient 바탕으로 grogu app (Windows x64용) 제작
grogu app는 battle.net의 UI와 기능을 모작으로 할 예정

## CMake 사용 먼저 익히기
- cmake-language 문서 확인하면서 빌드 시스템 커스터마이징 진행

## 코드 트래킹
- cefclient 바탕이라고 앞서 말한 것처럼 기존의 것을 최대한 참고
- 조금씩 수정하면서 비즈니스 로직을 완성해 나갈 예정 ..

## cef 버전
- 이진 배포 파일을 넘겨받아서 CMakeLists.txt를 수정해서 빌드 시스템 커스터마이징
- cef_binary_96.0.18+gfe551e4+chromium-96.0.4664.110_windows64_minimal/

## 업로드 파일
- 업로드되는 것은 빌드 시스템으로부터 발생한 것들을 제외한 코어 소스들만 올릴 예정
- 후에 빌드 시스템 글들 정리할 예정