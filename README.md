# 基于 Qt 的分布式即时通讯系统

## 🌟 项目介绍
本项目是一个**基于 Qt 构建的分布式即时通讯系统**，支持多用户在线聊天、消息发送、用户状态管理等功能。该系统采用**UDP 广播**进行通信，结合 **Qt 网络编程、多线程处理、信号槽机制**，提供**高效、流畅**的用户体验。

## 📸 项目截图（可选）
![project img](https://github.com/kawa1909/QT-QQNetWorking_Project/blob/master/images/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202025-03-16%20125625.png) 

## 🚀 主要功能
✅ **用户登录界面** - 选择用户后自动进入聊天界面  
✅ **多人在线聊天** - 通过 UDP 进行消息广播，实现即时通讯  
✅ **用户上线通知** - 新用户上线后会通知所有在线用户  
✅ **用户离线通知** - 用户退出时，会通知其他用户  
✅ **消息格式化** - 支持自定义字体、颜色、加粗、斜体、下划线等  
✅ **聊天记录保存** - 可将聊天记录导出为 `.txt` 文件  
✅ **界面美观简洁** - 采用 Qt Widgets 进行 UI 设计，操作直观  

## 🏗️ 技术栈
- **C++ / Qt 6** - 核心开发语言及 GUI 框架
- **UDP 网络通信** - 采用 `QUdpSocket` 进行数据传输
- **多线程** - 保障 UI 线程不被阻塞，提升响应速度
- **信号与槽机制** - 组件间高效解耦的事件驱动编程

## 📂 代码结构
```
├── login.h / login.cpp  # 用户登录界面
├── widget.h / widget.cpp  # 主聊天窗口
├── main.cpp  # 主程序入口
├── images/  # 头像资源
├── README.md  # 本项目文档
```

## 🔍 代码分析

### 1️⃣ `main.cpp` - 应用程序入口
```cpp
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login login;
    login.show(); // 显示登录界面
    return a.exec(); // 进入 Qt 事件循环
}
```
**分析：**
- `QApplication` 负责应用程序的初始化。
- `Login` 作为主界面对象，用户从此界面选择用户名后进入聊天界面。
- `a.exec()` 启动事件循环，使应用程序保持运行。

### 2️⃣ `login.cpp` - 登录界面逻辑
```cpp
for(int i=0; i<9; i++) {
    QToolButton *btn = new QToolButton(this);
    btn->setIcon(QPixmap(QString(":/images/%1.png").arg(listIcon[i])));
    btn->setText(list[i]);
    btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->vlayout->addWidget(btn);
}
```
**分析：**
- 通过 `QToolButton` 创建用户头像按钮，并设置其图标与文本。
- 采用 `QVBoxLayout` 布局管理，使用户按钮整齐排列。

### 3️⃣ `widget.cpp` - 聊天窗口逻辑
```cpp
udpSocket = new QUdpSocket(this);
udpSocket->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
connect(udpSocket, &QUdpSocket::readyRead, this, &Widget::receiveMessage);
```
**分析：**
- 绑定 UDP 端口，使程序能够接收网络消息。
- 监听 `readyRead` 信号，在消息到达时触发 `receiveMessage()` 处理。

```cpp
void Widget::sendMsg(Widget::msgType type)
{
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << type << this->getName();
    udpSocket->writeDatagram(array.data(), array.size(), QHostAddress::Broadcast, port);
}
```
**分析：**
- 采用 `QDataStream` 将消息编码为二进制流。
- 通过 `QUdpSocket::writeDatagram` 广播消息，使所有在线用户收到消息。

### 4️⃣ `receiveMessage()` - 处理接收消息
```cpp
void Widget::receiveMessage()
{
    QByteArray array;
    udpSocket->readDatagram(array.data(), size);
    QDataStream stream(&array, QIODevice::ReadOnly);
    int mytype;
    stream >> mytype;
    switch (mytype) {
        case Msg:
            stream >> name >> msg;
            ui->msgBrowser->append("[" + name + "] " + msg);
            break;
        case UserEnter:
            stream >> name;
            userEnter(name);
            break;
        case UserLeft:
            stream >> name;
            userLeft(name, time);
            break;
    }
}
```
**分析：**
- 读取 UDP 数据包并解析消息类型。
- 根据消息类型（聊天消息、用户上线、用户下线）进行不同的处理。
- 通过 `ui->msgBrowser->append()` 更新聊天窗口。

## 🔧 安装与运行
### 1️⃣ 环境依赖
- Qt 5.14.2 及以上
- C++11 及以上

### 2️⃣ 运行步骤
1. **克隆项目**
   ```bash
   git clone https://github.com/your_github_username/Qt_Distributed_Chat.git
   cd Qt_Distributed_Chat
   ```
2. **使用 Qt Creator 打开 `.pro` 项目文件**
3. **编译并运行**（可选择 `Release` 模式提高性能）
4. **选择用户名进入聊天界面**

## 🎯 未来优化方向
- **引入 TCP 可靠通信**，提升消息传输的稳定性
- **数据库存储聊天记录**，支持历史消息回溯
- **支持音视频通话**，提升用户互动体验
- **优化 UI 界面**，使其更美观现代化

## 📜 许可证
本项目基于 **MIT License** 开源，你可以自由修改、使用和分发。

---
💡 **欢迎 Star ⭐ 本项目，并 Fork 进行改进！**

