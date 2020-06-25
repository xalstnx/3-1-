# 3학년 1학기 네트워크 프로젝트
 
## 프로젝트의 목표
- C언어를 이용하여 웹서버를 구현한다. (타 언어 허용 불가)
- 서버와 웹브라우저의 동작 방식에 대해 학습한다.

## 프로젝트 내용
- Part 1: Client의 request message를 화면에 출력하는 "Web server" 제작.
  - Safari, Chrome 등 Web browser를 Client로 사용하여 Server에 접속한다.
  - Server로 전달된 request message 각 filed에 해당하는 값이 무엇인지 RFC 1945에서 찾아 레포트를 작성한다. https://tools.ietf.org/html/rfc1945
- Part II: Web server가 browser의 request에 response할 수 있도록 확장.
  - Browser로부터 받은 request message를 해석한다.
  - 요청 받은 파일에 대한 header를 작성한다.
  - header와 file을 붙여 HTTP response message를 완성하고 이를 client에게 전달한다.

## 프로젝트 주의사항
- server는 ./server <port_number> 형태로 동작해야 한다.
- 충돌 회피를 위해 port는 가급적 1024 이상의 번호를 사용하는 것이 좋다.
- server와 client를 동일한 컴퓨터에서 동작시킨다면, browser에서 접속을 위한 주소로 localhost나 127.0.0.1을 사용한다.
- "Content-Type"을 통해 최소한 html 파일을 인식할 수 있도록 만든다.
- server 제작 후 http://<machine name>:<port number>/<html file name>을 입력하여 정상 작동하는지 확인한다.
- 이 후 GIF, JPEG, MP3, PDF를 인식할 수 있도록 확장한다.
  
## 프로젝트 실행 및 디자인에 대한 도식
- makefile 실행

  ![makefile](https://user-images.githubusercontent.com/22045179/85653462-0b82a280-b6e8-11ea-880a-221d15c11b03.png)

- 클라이언트로부터 요청받은 파일을 GET or POST /파일명.확장자 형식으로 newbuf에 저장
![1](https://user-images.githubusercontent.com/22045179/85653469-0cb3cf80-b6e8-11ea-8795-3e18271c66e8.png)

- GET인지 POST인지 판별한후 /파일명.확장자 부분만 newpath에 저장함.
![2](https://user-images.githubusercontent.com/22045179/85653481-11788380-b6e8-11ea-82af-98291a9cb0cd.png)

- newpath에서 맨앞의 /부분을 떼어내고 뒷부분을 newfile에 저장.
- newfile에서 파일의 확장자 부분만(‘.’ 이후 부분) fileExtension에 저장.
![3](https://user-images.githubusercontent.com/22045179/85653489-13dadd80-b6e8-11ea-9e40-e4c368fc9d21.png)

- 각각의 파일의 확장자에 따른 Content-Type 출력값을 설정(html, gif, jpg, pdf, mp3 ...)
![4](https://user-images.githubusercontent.com/22045179/85653497-163d3780-b6e8-11ea-8219-7250b6c703f5.png)

- header를 생성하고 header와 파일을 붙여 클라이언트(브라우저)에 전달함.
![5](https://user-images.githubusercontent.com/22045179/85653511-1a695500-b6e8-11ea-9a47-1bae2653aac0.png)

## 동작예시
- .html 파일
  - 서버에는 GET한 파일, HOST의 IP주소와 포트, User-Agent와 요청에 대한 응답으로 허용되는 미디어 범위 목록인 Accept가 출력되고 클라이언트(브라우저)가 요청하는 파일을 보여줌
클라이언트는 서버로부터 요청한 파일에 대한 header와 파일명, 파일내용을 순서대로 보여줌

  ![6](https://user-images.githubusercontent.com/22045179/85653522-1ccbaf00-b6e8-11ea-8a97-4c9872506e92.png)
