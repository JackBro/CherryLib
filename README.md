# CherryLib

### Cherry Library - Win32/MFC Utility Library

Win32/MFC 기반의 Application을 개발하기 위해 필수적인 기능들을 모은 유용한 라이브러리입니다. 
이 프로젝트는 Visual Studio 2015 작성되었습니다.

1. CherryCtrl: Windows GDI+ 기반으로 제작된 UI Control DLL 라이브러리

  - 목적
  
    예쁘고 유연한 UI의 빠른 구현
  
  - 주요 기능 및 장점
  
    1. MFC와 GDI+를 사용하여 이미지 파일 포맷 사용의 다양성, Transparency 이미지를 지원하여 좀 더 매끄러운 UI 구현을 할 수 있다.
    2. 굳이 third-party 라이브러리를 사용하는 것보다는 Native Windows Control 기반의 이질감 없는 UI 컨트롤의 필요도 있을 것
    이기에 Windows 개발자들에게는 굉장히 유용한 라이브러리가 되리라 생각합니다.
    3. 9-Patch 지원

  - 단점
  
    1. GDI+ 때문에 느리다.
    2. Native API를 사용하기 때문에 Windows 기반에서만 사용 가능하다.
  
  - Classes

    CCherryDialog:
      CDialog 를 Subclassing 한 유연한 Dialog 컨트롤 슬라이드와 서서히 나타나는 기능, NonClient 영역 이미지로 덮는 기능.

    CCherryButton:
      Windows에서 일반적인 Button의 4가지 상태(Normal, Hover, Down, Disable)에 해당하는 이미지를 오너드로우 하여 뿌려주는 기능.

    CCherryFont:
      CherryCtrl 에서 사용하는 모든 문자열은 이 클래스를 사용하여 표현하고 관리하도록 한다.
      직접 사용하기 보단 상속하여 사용하는 상위 클래스 성격을 갖고 있다.

    CCherryImage:
      마찬가지로 CherryCtrl 에서 사용하는 모든 이미지는 클래스를 사용하여 표현하고 관리하도록 한다. 
      직접 사용하기 보단 상속하여 사용하는 상위 클래스 성격을 갖고 있다.

    CCherryEdit:
      CEdit 를 Subclassing 한 컨트롤. 배경과 폰트를 Custom 할 수 있다.

    CCherryListCtrl:
      CListCtrl을 Subclassing 한 컨트롤. 리스트 헤더/아이템의 배경색 설정이나 이미지를 입힐 수 있다.

    CCherryProressCtrl:
      CWnd를 Subclassing 하여 새로 구현한 Progress 컨트롤.

    CCherryMenu (준비 중):
      CMenu를 Subclassing 하여 스킨을 입힐 수 있도록 함.

    CCherryComboBox:
      CComboBox를 Subclassing 하여 기능 추가 및 스킨을 입힐 수 있도록 함.

    CCherryMemDC:
      CDC를 상속한 Memory Buffer DC, Double Buffering 구현시 사용하여 Image 깜빡임을 줄이도록 한다.

    CCherryToggleButton:
      CCherryButton을 상속한 확장 컨트롤이다. 버튼의 상태를 고정할 수 있는 토글 기능이 추가된 컨트롤이다.

    CCherryImageCtrl:
      CCherryImage와는 다르게 별도의 Window 속성이 부여된 이미지 컨트롤이다.

    CCherryLinkCtrl:
      CCherryStatic의 확장 컨트롤이다. 하이버링크 형식의 버튼 컨트롤 기능을 사용할 수 있다.

    CCherryCheckBox:
      CCherryWnd를 베이스로 새로 디자인 된 체크박스이다. 이미지, 텍스트 형태 또는 이미지와 텍스트를 합친 형태로 표현이 가능하다.

    CCherryRadioButton:
      CCherryCheckBox를 베이스로 디자인된 라디오 컨트롤이다. 체크박스와 마찬가지로 이미지, 텍스트 형태 또는 이미지와 텍스트를 합친 형태로 표현이 가능하다.

    CCherryFontByStatus:
      각 컨트롤에 사용되는 폰트의 상태를 관리하는 클래스이다.
    
  - 사용 샘플은 CherryExam 프로젝트 참조.

2. CherryUpdate: Live Update 모듈화 DLL

3. CherryUtil: 유틸리티성 함수들을 모아놓은 DLL 라이브러리

# License

    The MIT License (MIT)

    Copyright (c) 2016 Oh, Su-cheol <ogoons@hanmail.net>

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
