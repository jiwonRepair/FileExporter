# LibuvFileExportSample

Qt + libuv 기반으로 구현된 **초경량 비동기 파일 저장 샘플 프로젝트**입니다.  
멀티스레드, 멀티프로세스, 동적 메모리 할당 없이 완전히 **UI 블로킹 없이 동작하며**,  
libuv + QtConcurrent를 조합하여 **CPU 자원 사용을 극한으로 줄인** 백그라운드 파일 저장 기능을 제공합니다.

---

## ✅ 주요 특징

- ✅ QtConcurrent + libuv 조합으로 완전 비동기 실행
- ✅ UI 스레드 블로킹 없음
- ✅ 스레드 직접 생성 없음 (`QThread` 사용하지 않음)
- ✅ 동적할당 없음 (`new` 없이 모두 자동 메모리 관리)
- ✅ 진행률, 완료, 취소 모두 QML로 알림 가능
- ✅ 실행 경로에 간단한 텍스트 파일 저장 (예: signal_history.txt)

---

## 📁 구성 파일

| 파일명 | 설명 |
|--------|------|
| `SimpleFileExporter.h/.cpp` | libuv 기반 비동기 파일 저장 로직 |
| `main.cpp` | QML과 연동된 실행 진입점 |
| `Page2.qml` | 테스트 UI (버튼: 저장 / 취소) |
| `CMakeLists.txt` | Qt + libuv + QtConcurrent 빌드 설정 |
| `README.md` | 설명 문서

---

## ▶️ 실행 방법

1. Qt 6 프로젝트로 열기 (Core, Concurrent 필요)
2. QML에서 버튼 클릭 → 파일 저장
3. 중간에 취소 버튼 클릭 가능
4. 진행률은 콘솔로 확인 가능

---

## 💬 예제 시나리오

- 사용자가 "Export" 버튼을 누르면 텍스트 파일 저장이 비동기 시작됨
- UI는 전혀 멈추지 않음
- 저장 중 "Cancel" 누르면 바로 작업 중단
- `onSaveFinished`, `onSaveCancelled`, `onProgressChanged` 등 QML에서 시그널 연결 가능

---

## 🛠 환경

- Qt 6.x (QtConcurrent 포함)
- libuv (vcpkg 또는 시스템 경로)


## ✅ 최신 업데이트 내용 2025-03-28 13:21
feat(libuv-exporter): 스레드/동적할당 없이 완전 비동기 파일 저장 기능 최종 구현

- LibuvFileExporter 클래스 비동기 파일 저장 기능 완성
- 스레드, 멀티프로세스, 동적 메모리 할당 없이 작동 (libuv 루프 단독 사용)
- uv_run(UV_RUN_DEFAULT) 한 줄로 libuv 처리 루프 최소 실행
- Qt UI 스레드와 완전 분리되어 블로킹 현상 없음
- 진행률 및 완료 콜백은 QMetaObject::invokeMethod로 안전하게 전달
- formatter 기반 라인 구성 방식으로 다양한 포맷 대응 가능
- 실시간성 또는 저자원 환경에서도 안정적인 동작 보장
