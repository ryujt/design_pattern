# Design pattern - Command pattern


::: tip 예제 코드
[https://github.com/ryujt/design_pattern](https://github.com/ryujt/design_pattern)
:::


## 강의 개요

이번 강의에서는 Command 패턴이 무엇이고 언제 사용하는 지에 대해서 알아봅니다.

우선 위키백과의 정의를 살펴보면 다음과 같습니다.

::: tip 커맨드 패턴(command pattern)
커맨드 패턴(Command pattern)이란 요청을 객체의 형태로 캡슐화하여 사용자가 보낸 요청을 나중에 이용할 수 있도록 매서드 이름, 매개변수 등 요청에 필요한 정보를 저장 또는 로깅, 취소할 수 있게 하는 패턴이다.

커맨드 패턴에는 명령(command), 수신자(receiver), 발동자(invoker), 클라이언트(client)의 네개의 용어가 항상 따른다. 커맨드 객체는 수신자 객체를 가지고 있으며, 수신자의 메서드를 호출하고, 이에 수신자는 자신에게 정의된 메서드를 수행한다. 커맨드 객체는 별도로 발동자 객체에 전달되어 명령을 발동하게 한다. 발동자 객체는 필요에 따라 명령 발동에 대한 기록을 남길 수 있다. 한 발동자 객체에 다수의 커맨드 객체가 전달될 수 있다. 클라이언트 객체는 발동자 객체와 하나 이상의 커맨드 객체를 보유한다. 클라이언트 객체는 어느 시점에서 어떤 명령을 수행할지를 결정한다. 명령을 수행하려면, 클라이언트 객체는 발동자 객체로 커맨드 객체를 전달한다.

* 위키백과
:::

![](./pic-01.png)


## 미션

![](./pic-03.png)
![](./pic-02.png)


## 패턴 적용 전의 코드

``` js
class Socket {
    void onReceived(command, params) {
        switch (command) {
            case "upload": fileController.upload(params); break;
            case "askList": fileController.askList(params); break;
            case "delete": fileController.delete(params); break;
        }
    }
}

class FileController {
    void upload(params) {
        //
    }

    void askList(params) {
        //
    }

    void delete(params) {
        //
    }
}
```

## Command 패턴 적용 후

``` java
class Socket {
    void onReceived(command, params) {
        switch (command) {
            case "upload": fileController.execute(new CommandUpload(params)); break;
            case "askList": fileController.askList(new CommandGetList(params)); break;
            case "delete": fileController.delete(new CommandDelete(params)); break;
        }
    }
}

class FileController {
    void execute(command) {
        command.execute();
    }
}
```


## undo 기능 추가

``` java
class CommandDelete {
    ...
    public void execute() {}
    public void undo() {
        // TODO: 휴지통에서 꺼내오기 (파일 지울 때 보관처리)
    }
}

class Socket {
    void onReceived(command, params) {
        switch (command) {
            ...
            case "undo": fileController.undo(); break;
        }
    }
}

class FileController {
    void execute(command) {
        command.execute();
        history.push(command);
    }

    void undo() {
        const command = history.pop();
        command.undo();
    }
}
}
```