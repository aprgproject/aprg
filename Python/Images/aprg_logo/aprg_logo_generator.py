
import copy
import math
import random
from dataclasses import dataclass

import numpy as np
import skimage.io


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


def get_rgb_on_circle(scale, rgb_start, rgb_end):
    return round(scale*(rgb_end - rgb_start) + rgb_start)


def get_rgb_on_text(original_rgb, alpha_scale, scale_x):
    return 127 + 0.9*scale_x*128 + 0.1*alpha_scale*original_rgb


def are_colors_too_far(pixel1, pixel2):
    difference_limit = 24
    return (abs(int(pixel1[0]) - int(pixel2[0])) > difference_limit
            or abs(int(pixel1[1]) - int(pixel2[1])) > difference_limit
            or abs(int(pixel1[2]) - int(pixel2[2])) > difference_limit)


def get_darker(color, scale):
    darkest = 0.3
    remaining_scale = 1 - darkest
    scale = darkest + remaining_scale*scale
    return [color[0]*scale, color[1]*scale, color[2]*scale, color[3]]


def get_lighter(color, scale):
    lightest = 0.3
    remaining_scale = 1 - lightest
    scale = lightest + remaining_scale*scale
    return [min(255, color[0]/scale), min(255, color[1]/scale), min(255, color[2]/scale), color[3]]


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


def draw_pixel_at_circle(image, xy_position, top_left, bottom_right, color_end_points):
    x_position, y_position = xy_position
    color_start, color_end = color_end_points
    scale_x = (x_position-top_left[0])/(bottom_right[0]-top_left[0])
    scale_y = (y_position-top_left[1])/(bottom_right[1]-top_left[1])
    scale_hyp = math.dist(top_left, xy_position) / \
        math.dist(top_left, bottom_right)

    image[y_position, x_position] = [
        get_rgb_on_circle(scale_x,
                          color_start[0], color_end[0]),
        get_rgb_on_circle(scale_y,
                          color_start[1], color_end[1]),
        get_rgb_on_circle(scale_hyp, color_start[2], color_end[2]),
        255]


def add_to_edge_point(image, xy_position, edge_point_to_color):
    y_size, x_size, _ = np.shape(image)
    xy_size = (x_size, y_size)
    radius = 3
    for x_offset in range(-radius, radius+1):
        for y_offset in range(-radius, radius+1):
            xy_offset = (x_offset, y_offset)
            add_to_edge_point_with_offset(
                image, xy_position, xy_offset, xy_size, edge_point_to_color)


def add_to_edge_point_with_offset(image, xy_position, xy_offset, xy_size, edge_point_to_color):
    x_position, y_position = xy_position
    x_offset, y_offset = xy_offset
    radius = 3
    distance = math.dist((0, 0), (x_offset, y_offset))
    if distance <= radius:
        coordinate = (y_position+y_offset, x_position+x_offset)
        if coordinate[0] >= 0 and coordinate[0] < xy_size[0] and coordinate[1] >= 0 and coordinate[1] < xy_size[1]:
            new_color = get_darker(
                image[coordinate], 0.6+0.4*(distance/radius))
            if coordinate in edge_point_to_color:
                old_color = edge_point_to_color[coordinate]
                if (new_color[0] < old_color[0] or new_color[1] < old_color[1] or new_color[2] < old_color[2]):
                    edge_point_to_color[coordinate] = new_color
            else:
                edge_point_to_color[coordinate] = new_color


def draw_letter_a_pixel(image, xy_position, original_pixel, x_middle, x_size):
    x_position, y_position = xy_position
    color_scale = x_position/x_size
    alpha_scale = 1 - (abs(x_position-x_middle)/x_middle)
    image[y_position, x_position] = [get_rgb_on_text(original_pixel[0], alpha_scale, color_scale),
                                     get_rgb_on_text(
                                         original_pixel[1], alpha_scale, color_scale),
                                     get_rgb_on_text(original_pixel[2], alpha_scale, color_scale), 255*alpha_scale]


def draw_circle(image):
    y_size, x_size, _ = np.shape(image)
    xy_midpoint = ((x_size+1)//2, (y_size+1)//2)
    for x_position in range(x_size):
        for y_position in range(y_size):
            xy_position = (x_position, y_position)
            draw_circle_at_position(image, xy_position, x_size, xy_midpoint)


def draw_circle_at_position(image, xy_position, x_size, xy_midpoint):
    x_position, y_position = xy_position
    x_midpoint, y_midpoint = xy_midpoint
    radius = x_size*0.4
    distance = math.dist(xy_midpoint, xy_position)
    if distance < radius:
        multiplier_sin_function = radius/4
        multiplier_to_angle = math.pi/radius
        top_left = (x_midpoint-radius, y_midpoint-radius)
        bottom_right = (x_midpoint+radius, y_midpoint+radius)
        wave_y = y_midpoint - math.sin((x_position - top_left[0])
                                       * multiplier_to_angle)*multiplier_sin_function
        if y_position < wave_y:
            draw_circle_at_top_of_wave(
                image, xy_position, radius, distance, (top_left, bottom_right))
        else:
            draw_circle_at_bottom_of_wave(
                image, xy_position, radius, distance, (top_left, bottom_right))


def draw_circle_at_top_of_wave(image, xy_position, radius, distance, top_left_and_bottom_right):
    x_position, y_position = xy_position
    color_end_points = (
        four_corners_colors.top_left_color, four_corners_colors.top_right_color)
    draw_pixel_at_circle(
        image, xy_position, top_left_and_bottom_right[0], top_left_and_bottom_right[1], color_end_points)
    image[y_position, x_position] = get_lighter(
        image[y_position, x_position], 0.6 + (1-(distance/radius))*0.4)
    if radius*0.9 < distance:
        reverse_scale = 2.8-(distance/radius)*2  # 1 to 0.8
        image[y_position, x_position] = get_lighter(
            image[y_position, x_position], reverse_scale)


def draw_circle_at_bottom_of_wave(image, xy_position, radius, distance, top_left_and_bottom_right):
    x_position, y_position = xy_position
    color_end_points = (
        four_corners_colors.bottom_left_color, four_corners_colors.bottom_right_color)
    draw_pixel_at_circle(
        image, xy_position, top_left_and_bottom_right[0], top_left_and_bottom_right[1], color_end_points)
    image[y_position, x_position] = get_darker(
        image[y_position, x_position], 0.6 + (1-(distance/radius))*0.4)
    if radius*0.9 < distance:
        reverse_scale = 2.8-(distance/radius)*2  # 1 to 0.8
        image[y_position, x_position] = get_darker(
            image[y_position, x_position], reverse_scale)


def draw_letter_a(image):
    y_size, x_size, _ = np.shape(image)
    x_middle = (x_size+1)//2
    xy_size = (y_size, x_size)
    for x_position in range(x_size):
        for y_position in range(y_size):
            xy_position = x_position, y_position
            draw_letter_a_at_position(image, xy_position, xy_size, x_middle)


def draw_letter_a_at_position(image, xy_position, xy_size, x_middle):
    x_position, y_position = xy_position
    y_s_multiplier = xy_size[1]/1280
    # check notes for more info about the polynomials
    x_s = x_position*1280/xy_size[0]
    top_left = (7.641401711352939E-08*x_s**3 + -0.001469426845249755*x_s **
                2 + 0.03767793712239261*x_s + 907.881474319954) * y_s_multiplier
    bottom_left = (-5.658652163930147E-07*x_s**3 + -0.0004084999223478625 *
                   x_s**2 + -0.4834368000620288*x_s + 1018.7052478722) * y_s_multiplier
    top_right = (6.311007900381323E-06*x_s**3 + -0.02249420409310314*x_s **
                 2 + 27.20634107875812*x_s + -10127.11612409357) * y_s_multiplier
    bottom_right = (9.12861766646765E-06*x_s**3 + -0.02921189077082613 *
                    x_s**2 + 31.41800966282249*x_s + -10257.89060798793) * y_s_multiplier
    top_middle = (-2.752092040586441E-06*x_s**3 + 0.004841462611769976 *
                  x_s**2 + -2.473153786213333*x_s + 1012.876600748878) * y_s_multiplier
    bottom_middle = (-1.594617762447137E-06*x_s**3 + 0.003361228023313456 *
                     x_s**2 + -1.797687047234969*x_s + 921.5631013947169) * y_s_multiplier
    original = copy.deepcopy(image[y_position, x_position])
    if top_left < y_position < bottom_left and y_position > top_right:
        draw_letter_a_pixel(image, xy_position,
                            original, x_middle, xy_size[0])
    if top_right < y_position < bottom_right and y_position > top_left:
        draw_letter_a_pixel(image, xy_position,
                            original, x_middle, xy_size[0])
    if top_middle < y_position < bottom_middle and y_position > top_right:
        draw_letter_a_pixel(image, xy_position,
                            original, x_middle, xy_size[0])


def darken_edges(image):
    y_size, x_size, _ = np.shape(image)
    edge_point_to_color = {}
    for x_position in range(2, x_size-2):
        for y_position in range(2, y_size-2):
            xy_position = (x_position, y_position)
            if should_add_edge(image, xy_position):
                add_to_edge_point(image, xy_position, edge_point_to_color)
    for edge_point, new_color in edge_point_to_color.items():
        image[edge_point[0], edge_point[1]] = new_color


def should_add_edge(image, xy_position):
    x_position, y_position = xy_position
    return (are_colors_too_far(image[y_position, x_position], image[y_position, x_position-1])
            or are_colors_too_far(image[y_position, x_position], image[y_position, x_position+1])
            or are_colors_too_far(image[y_position, x_position], image[y_position-1, x_position])
            or are_colors_too_far(image[y_position, x_position], image[y_position+1, x_position]))


def generate_aprg_logo():
    image = skimage.io.imread('sample_small.png')

    print('starting draw_circle')
    draw_circle(image)
    print('starting draw_letter_a')
    draw_letter_a(image)
    print('starting darken_edges')
    darken_edges(image)
    print('starting draw_noise')
    # draw_noise(image)

    skimage.io.imsave('sample_logo_clean.png', image)


if __name__ == '__main__':
    generate_aprg_logo()
    print('done!')
