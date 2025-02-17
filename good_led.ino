// 인형 뽑기 성공 시 화면 송출
#include <Adafruit_GFX.h>   // Core graphics library
#include <P3RGB64x32MatrixPanel.h>
#include <string>

P3RGB64x32MatrixPanel matrix(25, 26, 27, 21, 22, 0, 15, 32, 33, 12, 5, 23, 4);

const uint16_t image[28][28] = {
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x4444, 0x0000, 0x4444, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0xFFFF, 0x0000, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x4444, 0x0000, 0x4444, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0xFFFF, 0x0000, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x4444, 0x0000, 0x4444, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0xFFFF, 0x0000, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0xFFFF, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}
};

void setup() {
    matrix.begin();
}

// 텍스트 출력 함수
void drawText(const char* text, int startX, int startY, int textSize) {
    matrix.setTextColor(matrix.colorHSV(255, 255, 255)); // White color
    matrix.setTextSize(textSize);
    int x = startX;
    int y = startY;

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == ' ') {
            x += 6 * textSize; // 간격 조정
        } else {
            matrix.setCursor(x, y);
            matrix.print(text[i]);
            x += 6 * textSize; // 다음 문자 위치
        }
    }
}

// 이미지를 출력하는 함수 (우측 하단 배치)
void drawImage() {
    int panelWidth = 64;  // LED 패널 너비
    int panelHeight = 32; // LED 패널 높이
    int imageWidth = 28;  // 이미지 너비
    int imageHeight = 28; // 이미지 높이

    // 우측 하단에 배치하기 위한 시작 위치 계산
    int offsetX = panelWidth - imageWidth;  // X축 시작 위치
    int offsetY = panelHeight - imageHeight; // Y축 시작 위치

    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < imageWidth; x++) {
            uint16_t color = image[y][x];
            matrix.drawPixel(offsetX + x, offsetY + y, color);
        }
    }
}

// 테두리를 출력하는 함수
void drawBorder() {
    uint16_t borderColor = 0x07E0; // 테두리 색상, 초록색

    // 상단 및 하단 테두리
    for (int x = 0; x < 64; x++) {
        matrix.drawPixel(x, 0, borderColor);      // 상단
        matrix.drawPixel(x, 31, borderColor);    // 하단
    }

    // 좌측 및 우측 테두리
    for (int y = 0; y < 32; y++) {
        matrix.drawPixel(0, y, borderColor);     // 좌측
        matrix.drawPixel(63, y, borderColor);    // 우측
    }
}

void loop() {
    matrix.fillScreen(0); // 화면 지우기

    
    drawText("YOU", 5, 7, 1);

    
    drawText("WINS!", 5, 15, 1);

    // 이미지 출력
    drawImage();

    // 테두리 그리기
    drawBorder();

    delay(5000); // 5초 대기
}