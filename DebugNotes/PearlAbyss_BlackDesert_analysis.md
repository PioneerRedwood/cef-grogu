# BlackDesert of Pearl Abyss

## directories
### bin, bin64
There are common parts, x86/x86-64 architecture
#### host directory
- CoherntUI_Host.exe
    - 불가리아 소재의 Cohernt Labs에서 제공하는 최신 게임 UI 라이브러리 제작사의 제품 중 하나
    - 웹 페이지를 구성하는 요소(HTML, JS, CSS)를 게임 엔진(C++)에 적용
    - [참고](https://coherent-labs.com/)
- D3DCompiler_43.dll: DirectX에서 사용하는 DLL. 
- ffmpegsumo.dll: 크롬에서 사용되는 라이브러리
- icudt.dll: 국제 Unicode 관련 라이브러리. [참고](https://www.fileinspect.com/fileinfo/icudt-dll/)
- libEGL.dll: 크롬에서 쓰이는 ANGLE libEGL 동적 링크 라이브러리. Mozila Foundation에서 개발됨. [참고](https://www.fileinspect.com/fileinfo/libegl-dll/)
- libGLESv2.dll: 위와 비슷
- pak files
- locales(local packages)
- disk_cache(data files)

#### dlls
- AkSoundEngineDLL.dll: AudioKinetic 음향 엔진 [참고](https://www.dll4free.com/aksoundenginedll.dll.html)
- AnselSDK32.dll / AnselSDK64.dll: NVIDIA 캡쳐 관련 라이브러리 [참고](https://developer.nvidia.com/ansel)
- api-ms-win-core-*-l1-1-0.dll (-l1-1-0 suffix): UWP(유니버설 Windows 플랫폼)의 일부, Win32 API 라이브러리 [참고](https://docs.microsoft.com/ko-kr/uwp/win32-and-com/win32-apis)
- api-ms-win-crt-*-l1-1-0.dll
- bink2w32.dll / bink2w64.dll: 게임을 위한 비디오 코덱, RAD Game Tools(에픽 게임즈의 자회사)가 개발함 [참고](https://ko.dll-files.com/bink2w32.dll.html)
- CoherentUI.dll
- concrt140.dll: VS 2015를 사용해 빌드된 MSVC 재배포 가능 패키지 설치 런타임 라이브러리 중 하나 [참고](https://ko.dll-files.com/concrt140.dll.html)
- D3DCompiler_43.dll: Microsoft DirectX 사용 시 필요 라이브러리 [참고](https://ko.dll-files.com/d3dcompiler_43.dll.html)
- d3dX9/11_43.dll: 위와 동일
- dbgcore.dll: Windows 코어 디버깅 헬퍼 [참고](https://www.exefiles.com/ko/dll/dbgcore-dll/)
- dbghelp.dll: 파일 내 혹은 런타임 프로세스에서 디버그 정보 분석 [참고](http://p-nand-q.com/python/procmon.html)
- libxl.dll: 엑셀 파일 읽기/쓰기 라이브러리 [참고](https://ko.dll-files.com/libxl.dll.html)
- MachineIdLib.dll: ? 
- mfc140u.dll: MFCDLL 공유 라이브러리 [참고](https://www.dll-files.com/mfc140u.dll.html)
- mfcm140u.dll: MFC 관리 라이브러리, 정품 버전 [참고](https://www.dll-files.com/mfcm140u.dll.html)
- msvcp100 / 140.dll: MSVC의 일부, VC++로 개발된 프로그램을 실행하는데 필요 [참고](https://www.dll-files.com/msvcp100.dll.html)
- msvcr100.dll: 위와 동일
- portaudio_x86.dll / portaudio_x64.dll: PortAudio의 사전 컴파일된 바이너리 [참고](https://www.dll-files.com/portaudio_x86.dll.html)
- ucrtbase.dll: MS C 런타임 라이브러리 [참고](https://www.dll-files.com/ucrtbase.dll.html)
- umbraoptimizer32.dll / umbraoptimizer64.dll: 
    - ? 위쳐3, Unity 에디터에서 사용됨 [참고1](https://www.dll-files.com/umbraoptimizer64.dll.html) 
    - Windows OS의 필수 시스템 파일을 참고하는 라이브러리 [참고2](https://wikidll.com/other/umbraoptimizer64-dll)
- vccorlib140.dll: MSVC WinRT 코어 라이브러리 [참고](https://www.dll-files.com/vccorlib140.dll.html)
- vcomp140.dll: MSVC OpenMP 런타임
- vcruntime140.dll: MS C 런타임 라이브러리 [참고](https://www.dll-files.com/vcruntime140.dll.html)
- xinput1_3.dll: MS 공통 컨트롤러 API [참고](https://www.dll-files.com/xinput1_3.dll.html)
- zlibwapi.dll: ZIP 데이터 압축 / 파일 입출력 라이브러리 [참고](https://www.dll-files.com/zlibwapi.dll.html)

#### etc
BDOKR.ini
BDOKRTest.ini
GameGuard.des
BlackDesert32.exe / BlackDesert64.exe

### Cache\91
- MyJournal/bcf files
#### bcf files
- Base
- Character
- Character_Custom
- Character_Equip
- Character_GuildAllianceBasic
- Character_GuildAllianceMarkBasic
- Character_GuildBasic
- Character_GuildMarkBasic
- Character_PcBasic
- Character_Skill
- Character_VehicleBasic
- Character_VehicleEquip
- Guild
- GuildAlliance
- User
- UserGameOption
- UserUi
- UserUiInfo
- Vehicle

### EasyAntiCheat
- An anti-cheating program serviced by EpicGames
- official site https://www.easy.ac/en-us/

### locales
- local packages, pak files

### Log
- json format logs
- Date, ThreadId, LogType, ServiceLogLevel, LogLevel, ErrorNo, ErrorString, Log

### patch_temp 
- hiddle & empty

### Paz
- paz files

## files
### dll
- d3dcompiler_43/47.dll
- expapply.dll: Pocket Soft RTPatch 서버용 라이브러리 [참고](https://ko.dll-files.com/expapply.dll.html)
- libcef.dll: CEF 라이브러리
- libEGL.dll
- libGLESv2.dll
- msvcp100/140.dll
- msvcr100.dll
- PAGAuth.dll: Pearl Abyss Google Auth 라이브러리
- vcruntime140.dll
- widevinecdmadapter.dll: 
    - CDM: Content Decryption Module(콘텐츠 암호화 모듈) 웹 브라우저와 Digital Rights Management를 구현하는 소프트웨어 간의 통신 채널을 제공하기 위한 W3C 표준 권장 사양이다.
    - Widevine: 구글의 DRM 기술로 다양한 암호화 체계와 하드웨어 보안을 지원해 콘텐츠 소유자가 정의한 규칙에 따라 분산된 비디오 콘텐츠에 대한 소비자 엑세스를 관리 또는 제한한다.
- steam_api.dll

### exe
- BlackDesertEAC.exe
- BlackDesertLauncher.exe
- dotNetFx45_Full_setup.exe
- PERS.exe
- unins000.exe
- wow_helper.exe

### log
- debug.log
- console.log
- update.log

### etc
- ads_files
- ads_version
- cef.pak
- cef_100/200_percent.pak
- cef_extensions.pak
- config.ini
- Cookies
- Cookies-journal
- devtools_resources.pak
- icudtl.dat
- patcher_files_version
- patcher_version
- PatchUI.json
- service.ini
- unins000.dat
- unins000.msg
- UseGPU
- wow_helper.exe

## Extensions
- pak: "packed", 비디오 게임 혹은 크롬 웹 브라우저 등에서 사용되는 아카이브 파일
- bcf: BIM Collaboration Format? [참고](https://technical.buildingsmart.org/standards/bcf/)
- paz: 검은사막용 데이터 파일

## 작성 후기
처음에는 프로그램에서 제공하는 기능에 쓰이는 DLL의 종류를 알고 싶었다.

디렉토리 내에 존재하는 DLL과 그외 파일들을 구글링하며 시간을 보냈다.

모든 것을 알지는 못했지만 내가 무엇이 부족하고 흥미로운 분야의 파일을 찾을 수 있었다:
- CoherentUI
- AKSoundEngine.dll
- bink2w32.dll
- MS build & redistribution dlls
- PortAudio.dll
- expapply.dll
- widevinecdmadapter.dll