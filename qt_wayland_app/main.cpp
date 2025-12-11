#include <QApplication>
#include <QDebug>
#include <QProcessEnvironment>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWindow>
#include <QScreen>
#include <QFont>
#include <QCoreApplication>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

// 自定义绘图控件
class GraphicWidget : public QWidget {
    Q_OBJECT
public:
    GraphicWidget(QWidget *parent = nullptr) : QWidget(parent), angle(0) {
        setFixedSize(300, 300);
        
        // 设置定时器，实现动画效果
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [this]() {
            angle += 1;
            if (angle >= 360) angle = 0;
            update();
        });
        timer->start(50);
    }
    
    ~GraphicWidget() {
        timer->stop();
    }
    
protected:
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);
        
        QPainter painter(this);
        
        // 设置抗锯齿
        painter.setRenderHint(QPainter::Antialiasing, true);
        
        // 清空背景
        painter.fillRect(rect(), QColor(240, 240, 240));
        
        // 绘制一个旋转的彩色矩形
        painter.translate(width() / 2, height() / 2);
        painter.rotate(angle);
        
        QPen pen(Qt::black, 2);
        painter.setPen(pen);
        
        // 绘制彩色填充矩形
        QLinearGradient gradient(-100, -100, 100, 100);
        gradient.setColorAt(0, Qt::red);
        gradient.setColorAt(0.3, Qt::yellow);
        gradient.setColorAt(0.6, Qt::green);
        gradient.setColorAt(1, Qt::blue);
        
        painter.setBrush(gradient);
        painter.drawRect(-100, -100, 200, 200);
        
        // 绘制中心圆
        painter.setBrush(Qt::white);
        painter.drawEllipse(-30, -30, 60, 60);
        
        // 绘制旋转指示器
        painter.setBrush(Qt::black);
        painter.drawRect(0, -10, 80, 20);
    }
    
private:
    int angle;
    QTimer *timer;
};

int main(int argc, char *argv[]) {
    // 设置Wayland环境变量
    qputenv("QT_QPA_PLATFORM", "wayland");
    
    QApplication a(argc, argv);
    
    QWidget window;
    window.setWindowTitle("Qt Wayland图形渲染示例");
    window.resize(500, 400);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(&window);
    
    // 标题
    QLabel *titleLabel = new QLabel("Qt Wayland图形渲染示例");
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);
    
    // 图形显示区域
    GraphicWidget *graphicWidget = new GraphicWidget();
    mainLayout->addWidget(graphicWidget);
    
    // 信息显示
    QLabel *infoLabel = new QLabel("这是一个在Wayland上渲染的旋转彩色矩形");
    infoLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(infoLabel);
    
    // Wayland平台信息
    QLabel *platformLabel = new QLabel();
    platformLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(platformLabel);
    
    // 按钮
    QPushButton *closeButton = new QPushButton("关闭");
    mainLayout->addWidget(closeButton);
    
    // 连接信号槽
    QObject::connect(closeButton, &QPushButton::clicked, &window, &QWidget::close);
    
    // 显示窗口
    window.show();
    
    // 输出平台信息
    QString platform = QGuiApplication::platformName();
    platformLabel->setText(QString("当前平台: %1").arg(platform));
    
    qDebug() << "Running on platform:" << platform;
    qDebug() << "Wayland compositor available:" << (platform == "wayland");
    
    // 显示Wayland相关环境变量
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    qDebug() << "WAYLAND_DISPLAY:" << env.value("WAYLAND_DISPLAY", "Not set");
    qDebug() << "XDG_RUNTIME_DIR:" << env.value("XDG_RUNTIME_DIR", "Not set");
    
    return a.exec();
}

// 包含自动生成的moc文件
#include "main.moc"
