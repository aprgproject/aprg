import math
import random
from dataclasses import dataclass

import numpy as np
import skimage.io


@dataclass
class Coordinate:
    x_position: float = 0.0
    y_position: float = 0.0


@dataclass
class FourCornersColors:
    top_left_color: tuple = (0.0, 0.0, 0.0)
    top_right_color: tuple = (0.0, 0.0, 0.0)
    bottom_left_color: tuple = (0.0, 0.0, 0.0)
    bottom_right_color: tuple = (0.0, 0.0, 0.0)


# four_corners_colors = FourCornersColors(
#     top_left_color=(76, 129, 134),
#     top_right_color=(210, 223, 225),
#     bottom_left_color=(127, 85, 131),
#     bottom_right_color=(15, 10, 16)
# )
four_corners_colors = FourCornersColors(
    top_left_color=(14, 178, 210),
    top_right_color=(255, 255, 255),
    bottom_left_color=(179, 1, 196),
    bottom_right_color=(0, 0, 0)
)


def get_color_for_normal_background(xy_position, xy_size):
    x_position, y_position = xy_position
    x_size, y_size = xy_size
    x_scale, y_scale = x_position/x_size, y_position/y_size

    hyp_scale = calculate_hyp_scale(xy_position, xy_size)
    numerators = calculate_numerators(xy_position, xy_size)
    denominator = calculate_common_denominator(xy_position, xy_size)

    result = [n/denominator for n in numerators]
    for rgb_index in range(3):
        result[rgb_index] = calculate_rgb(
            result, rgb_index, (x_scale, y_scale), hyp_scale)
    return result


def calculate_numerators(xy_position, xy_size):
    x_size, y_size = xy_size
    result = [0, 0, 0]
    for i in range(3):
        result[i] = (
            (calculate_distance((xy_position[0], xy_position[1]), (x_size-1, y_size-1))
             * four_corners_colors.top_left_color[i] +
             calculate_distance(
                 (x_size-1, 0), (xy_position[0], xy_position[1]))
             * four_corners_colors.top_right_color[i] +
             calculate_distance(
                 (0, y_size-1), (xy_position[0], xy_position[1]))
             * four_corners_colors.bottom_left_color[i] +
             calculate_distance((0, 0), (xy_position[0], xy_position[1]))
             * four_corners_colors.bottom_right_color[i])
        )
    return result


def calculate_common_denominator(xy_position, xy_size):
    x_size, y_size = xy_size
    top_left = calculate_distance((0, 0), xy_position)
    top_right = calculate_distance((x_size-1, 0), xy_position)
    bottom_left = calculate_distance((0, y_size-1), xy_position)
    bottom_right = calculate_distance((x_size-1, y_size-1), xy_position)
    return top_left + top_right + bottom_left + bottom_right


def calculate_rgb(result, rgb_index, xy_scale, hyp_scale):
    x_scale, y_scale = xy_scale
    return min(255,
               (96 + 0.7*result[rgb_index]
                + 0.1*x_scale * four_corners_colors.top_left_color[rgb_index]
                + 0.1*y_scale *
                four_corners_colors.bottom_left_color[rgb_index]
                + 0.1*(1-hyp_scale)*four_corners_colors.top_right_color[rgb_index]))


def calculate_hyp_scale(xy_position, xy_size):
    x_size, y_size = xy_size
    return calculate_distance((0, 0), xy_position) / calculate_distance((0, 0), (x_size-1, y_size-1))


def calculate_distance(point1, point2):
    return math.dist(point1, point2)


def get_rgb_on_circle(scale, rgb_start, rgb_end):
    return round(scale*(rgb_end - rgb_start) + rgb_start)


def apply_noise(color, noise_scale):
    return color*(1-noise_scale) + random.randint(0, 255)*(noise_scale)


def get_with_noise(color, noise_scale):
    return [apply_noise(color[0], noise_scale),
            apply_noise(color[1], noise_scale),
            apply_noise(color[2], noise_scale), color[3]]


def draw_noise(image):
    y_size, x_size, _ = np.shape(image)
    x_middle = (x_size+1)//2
    for x_position in range(x_size):
        for y_position in range(y_size):
            noise_scale = 0.05*(abs(x_position-x_middle)/x_middle) + 0.05
            if image[y_position, x_position, 3] != 0:
                image[y_position, x_position] = get_with_noise(
                    image[y_position, x_position], noise_scale)


def draw_pixel_for_title(image, position, top_left, bottom_right, color_end_points):
    x_position, y_position = position
    color_start, color_end = color_end_points
    x_scale = (x_position-top_left[0])/(bottom_right[0]-top_left[0])
    y_scale = (y_position-top_left[1])/(bottom_right[1]-top_left[1])
    scale_hyp = math.dist(top_left, (x_position, y_position)
                          ) / math.dist(top_left, bottom_right)

    image[y_position, x_position] = [
        get_rgb_on_circle(x_scale,
                          color_start[0], color_end[0]),
        get_rgb_on_circle(y_scale,
                          color_start[1], color_end[1]),
        get_rgb_on_circle(scale_hyp, color_start[2], color_end[2]),
        255]


def fill_normal_background(image):
    y_size, x_size, _ = np.shape(image)
    sizes = (x_size, y_size)
    for x_position in range(x_size):
        for y_position in range(y_size):
            color = get_color_for_normal_background(
                (x_position, y_position), sizes)
            image[y_position, x_position] = [round(color[0]), round(
                color[1]), round(color[2]), 255]


def fill_title_background(image):
    y_size, x_size, _ = np.shape(image)
    wave_radius = x_size/100
    multiplier_sin_function = wave_radius/4
    multiplier_to_angle = math.pi/wave_radius
    top_left = (0, 0)
    bottom_right = (x_size, y_size)
    for x_position in range(x_size):
        y_wave_position = (0.8 + 0.1 * (x_position/x_size)) * y_size
        for y_position in range(y_size):
            sin_wave = math.sin(x_position * multiplier_to_angle) * \
                multiplier_sin_function
            wave_y = y_wave_position - sin_wave

            if y_position < wave_y:
                draw_pixel_for_title(
                    image, (x_position, y_position), top_left, bottom_right,
                    (four_corners_colors.top_left_color, four_corners_colors.top_right_color))
            else:
                draw_pixel_for_title(
                    image, (x_position, y_position), top_left, bottom_right,
                    (four_corners_colors.bottom_left_color, four_corners_colors.bottom_right_color))


def generate_normal_background():
    print('reading file')
    image = skimage.io.imread('sample_small.png')
    print('starting fill_normal_background')
    fill_normal_background(image)
    print('starting draw_noise')
    draw_noise(image)
    print('saving file')
    skimage.io.imsave('normal_background.png', image)


def generate_title_background():
    print('reading file')
    image = skimage.io.imread('sample_small.png')
    print('starting fill_title_background')
    fill_title_background(image)
    print('starting draw_noise')
    draw_noise(image)
    print('saving file')
    skimage.io.imsave('title_background.png', image)


if __name__ == '__main__':
    # generate_normal_background()
    generate_title_background()
    print('done!')
