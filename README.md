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
  
## 프로젝트 실행
###makefile 실행
