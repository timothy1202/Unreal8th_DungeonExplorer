#  Dungeon Explorer

C++로 구현한 콘솔 기반 던전 탐험 RPG입니다.<br>
플레이어가 스테이지를 진행하며 전투, 아이템 사용, 이벤트를 경험하는 게임입니다.

## 프로젝트 소개
- 개발 기간: 2026.03.26 ~ 2026.04.01
- 팀원 수: 6명

## 주요 기능
- 스테이지 진행
- 전투 시스템
- 아이템 및 인벤토리
- 상점 시스템
- 몬스터 및 보스전
- 캐릭터 및 직업 시스템
- 로그 시스템
- Sprite 및 애니메이션 출력

## 개발 환경
- Language: C++
- Platform: Console

## 실행 방법
1. 프로젝트를 빌드합니다.
2. 실행파일을 실행합니다.
3. 콘솔 창에서 안내에 따라 입력을 진행합니다.

## 클래스 / 시스템 설명
- **GameFlowManager**: 게임의 전체 진행 순서를 제어합니다.
- **GameManager**: 플레이어와 인벤토리를 관리합니다.
- **BattleSystem**: 플레이어와 몬스터 간 전투를 처리합니다.
- **StageManager**: 스테이지 변경/진입 이벤트와 랜덤 이벤트 실행을 담당합니다
- **Stage**: 각기 다른 진입 이벤트와 랜덤 이벤트를 보유하고 있습니다.
- **Item, Inventory**: 아이템 획득, 착용, 보관을 담당합니다.
- **Store**: 아이템 구매, 판매를 담당합니다.
- **Monster, Boss**: 범위 내 랜덤으로 스텟을 가진 몬스터와 보스를 생성, 관리합니다. 
- **Character, Job**: 캐릭터 정보를 관리하며, 직업 별로 서로 다른 능력치 가중치를 적용합니다.
- **Log System**: 게임 내 이벤트 및 시스템 메시지를 출력합니다.
- **Sprite, Animation**: 전투 시 몬스터 스프라이트와 몬스터 피격, 몬스터 공격 애니메이션을 표현합니다.

## 역할 분담
* 김재성
    * 로그 시스템
    * Sprite 및 애니메이션
* 이건이
    * 게임 진행 흐름
    * 게임 매니저
* 박광훈
    * 아이템
    * 인벤토리
    * 상점
* 김대현
    * 몬스터
    * 보스 
* 조범근
    * 전투 시스템
    * 스테이지
* 고예현
    * 캐릭터
    * 직업

## 협업 방식
각 기능을 분담하여 각자의 브랜치에서 작업하고, 이를 하나의 프로젝트로 통합하는 방식으로 협업하였습니다.

## 트러블 슈팅
<details>
    <summary><b>Git 충돌(.vcxproj, .vcxproj.filter 파일)</b></summary>
    <br>
    <b>발생 원인</b><br>
    <ul>
        <li>각 브랜치에서 파일을 추가하는 과정에서 <code>.vcxproj</code>, <code>.vcxproj.filters</code> 파일도 함께 수정하였습니다.</li>
        <li>병합 과정에서 해당 파일들에 충돌이 발생했고, 한쪽 변경만 반영할 경우 다른 브랜치에서 추가한 파일이 Visual Studio에서 보이지 않는 문제가 발생했습니다.</li>
        <li>또한 충돌을 수동으로 해결하는 과정에서 XML 태그 일부가 누락된 채 반영되는 경우가 있었고, <code>.vcxproj</code>에서 누락되면 프로젝트가 정상적으로 로드되지 않았으며, <code>.vcxproj.filters</code>에서 누락되면 솔루션 탐색기에서 파일 분류가 올바르게 표시되지 않았습니다.</li>
    </ul>
    <b>해결 방법</b>
    <ul>
        <li>변경 내용을 비교하여 필요한 항목이 모두 반영되도록 IDE에서 직접 수정했습니다.</li>
    </ul>
    <b>결과</b>
    <ul>
        <li>프로젝트가 정상적으로 로드되도록 복구했고, 솔루션 탐색기에서도 파일이 올바르게 표시되었습니다.</li>
    </ul>
</details>

<details>
    <summary><b>GameManager와 BattleManager 간의 역할 및 접근 권한 중복 현상</b></summary>
    <br>
    <b>발생 원인</b>
    <ul>
        <li>GameManager와 BattleManager가 담당하는 역할이 일부 겹치고, 필요한 정보에 접근하는 구조도 중복되는 경우가 발생했습니다.</li>
    </ul>
    <b>해결 방법</b>
    <ul>
        <li>GameManager와 BattleManager가 다룰 책임을 다시 정리하고, GameFlowManager가 두 Manager를 관리하는 구조로 변경했습니다.</li>
    </ul>
    <b>결과</b>
    <ul>
        <li>Manager 간 직접적인 결합을 줄이고, GameFlowManager를 기준으로 시스템 연결 구조를 정리했습니다.</li>
    </ul>
</details>

<details>
    <summary><b>특정 클래스의 비대화 문제</b></summary>
    <br>
    <b>발생 원인</b>
    <ul>
        <li>LogSystem은 처음에는 간단한 통계 추적 기능을 동반하는 특수 메세지 출력을 목적으로 했지만, 기능이 추가되며 통계 기능과 레이아웃에 맞는 특수 메세지 출력까지 함께 담당하게 되었습니다.</li>
        <li>GameManager는 입력-캐릭터 생성 과정을 다루는 중 과도한 책임이 생긴다고 판단되어, 게임 흐름 전체를 관리하기 위한 GameFlowManager를 생성하게 되었습니다.</li>
        <li>이후 GameFlowManager는 입력, 입력 값 판별, 다음 게임 흐름 진행, 각 단계 사이 사용자 피드백을 위한 LogSystem 호출까지 맡게 되며 비대해졌습니다.</li>
    </ul>
    <b>회고</b>
    <ul>
        <li>LogSystem은 통계를 추적하는 클래스와 메세지 출력을 전문적으로 담당하는 클래스로 분리하는 것이 디버깅과 기능 추가에 더 도움이 되었을 것이라고 판단했습니다.</li>
        <li>또한 GameFlowManager는 흐름만 맡고, Input과 Log 호출 관리 등을 따로 분리시키는 구조가 더 적절했을 것이라고 판단했습니다.</li>
    </ul>
</details>

<details>
    <summary><b>LayoutManager - SpriteManager ANSI 코드 문제</b></summary>
    <b>발생 원인</b>
    <ul>
        <li>텍스트 기반 환경에서 그래픽과 유사한 화면을 구현하고자 ANSI 이스케이프 코드를 이용해 색상을 표현하고, SpriteManager를 통해 이를 관리하고자 했습니다.</li>
        <li>다만 ANSI 코드는 출력상으로는 텍스트의 자릿수를 차지하지 않지만, string을 다루는 함수에서는 ANSI 코드 또한 문자열 길이로 인식되어 레이아웃 배치를 깨뜨리는 버그가 발생했습니다.</li>
    </ul>
    <b>해결 방법</b>
    <ul>
        <li>기존에 사용하던 replace() 대신, ANSI 코드를 고려하여 substr()을 통한 문자 조합 방식으로 일부 문제를 해결하고자 했습니다.</li>
    </ul>
    <b>한계</b>
    <ul>
        <li>기본 텍스트 규격으로 되돌리는 코드의 간섭으로 인해 의도와 다른 색상이 출력되는 문제가 남아 있었고, 현재 방식만으로는 이에 한계가 있었습니다.</li>
    </ul>
</details>

## 화면 구성
![alt text](DungeonExplorer/Image/Layout.png)

* Main Layout: 전반적인 콘텐츠를 보여주는 공간 
* Side Layout: 플레이어 상태 창을 보여주는 공간
* Log Layout: 이벤트, 시스템 메시지를 보여주는 공간
* Input Layout: 사용자의 입력을 받는 공간

## 시연 영상

* [Youtube 링크](https://www.youtube.com/watch?v=GuemXqiNJm0)