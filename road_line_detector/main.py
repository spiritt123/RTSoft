import cv2
import numpy as np

#Гаусово размытие
def canny(img):
    img = cv2.cvtColor(img, cv2.COLOR_BGR2BGRA)
    blur = cv2.GaussianBlur(img, (5,5), 0)
    return cv2.Canny(blur, 50, 120)

def make_coordinates(image, line_parameters):   #функция, задающая координаты прямой
    slope, intercept = line_parameters
    y1 = image.shape[0]
    y2 = int(y1 * (3/5) + 50)
    x1 = int((y1 - intercept) / slope)
    x2 = int((y2 - intercept) / slope)
    return np.array([x1, y1, x2, y2])


def average_slope_intercept(image, lines):
    left_fit = []
    right_fit = []
    while lines is not None:
        for line in lines:
            x1, y1, x2, y2 = line.reshape(4)
            parameters = np.polyfit((x1, x2), (y1, y2), 1)
            slope = parameters[0]
            intercept = parameters[1]
            if slope < 0:
                left_fit.append((slope, intercept))
            else:
                right_fit.append((slope, intercept))
        left_fit_average = np.average(left_fit, axis=0)
        left_line = make_coordinates(image, left_fit_average)
        right_fit_average = np.average(right_fit, axis=0)
        right_line = make_coordinates(image, right_fit_average)
        return np.array([left_line, right_line])

def display_lines(image, lines):    #функция для отрисовки линий
    line_image = np.zeros_like(image)
    x_l = lines[0][0]
    x_r = lines[1][0]
    dx = 1920 - x_r - x_l 
    if lines is not None:
        for x1, y1, x2, y2 in lines:
            cv2.line(line_image, (x1, y1), (x2, y2), (255, 0, 250), 5)
        # линия, указывающая направление желательного смещения
        cv2.line(line_image, (int((x_r + x_l) / 2), 1080), (int((960 - dx)) , 900), (255, 255, 255), 5)
    return line_image


def trapezoid(image):
    height = image.shape[0]
    polygons = np.array([(20, height), (1300, height), (900, 700), (300, 700)])  
    mask = np.zeros_like(image)
    cv2.fillPoly(mask, np.array([polygons], dtype=np.int64), 1024)
    masked_image = cv2.bitwise_and(image, mask)
    return masked_image

def main() : 
    name_video = "test2.mp4"
    video = cv2.VideoCapture(name_video)

    cv2.waitKey(1)

    state = 3; # 0 - обычная картинка
               # 1 - фильтр чёрнобелый
               # 2 - обрезка трапецией 
               # 3 - отрисовка линий
               #

    while video.isOpened():
        _, frame = video.read()

        cv2.namedWindow(name_video, cv2.WINDOW_NORMAL)
        cv2.resizeWindow(name_video,640,360)

        copy_img = np.copy(frame)

        try:
            if state > 0:
                frame = canny(frame)
            if state > 1:
                frame = trapezoid(frame)
            if state > 2:
                lines = cv2.HoughLinesP(frame, 2, np.pi/180, 100, np.array([()]), minLineLength = 100, maxLineGap = 50)
                averaged_lines = average_slope_intercept(frame, lines)
                line_image = display_lines(copy_img, averaged_lines)
                combo = cv2.addWeighted(copy_img, 0.8, line_image, 0.5, 1)
                cv2.imshow(name_video, combo)
            if state < 3:
                cv2.imshow(name_video, frame)
        except:
            pass

        wait = cv2.waitKey(1)
        for i in range(0, 4):
            if (wait & 0xFF == (ord('0') + i)):
                state = i
                break

        if (wait & 0xFF == 32):
            while 1:
                wait = cv2.waitKey(1)
                if (wait & 0xFF == 32):
                    break
        if (wait & 0xFF == 27):
            video.release()
            cv2.destroyAllWindows()
            break
main()
