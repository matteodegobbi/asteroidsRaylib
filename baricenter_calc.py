first = [(-10, -10), (0, -16), (+10, -12), (+6, 0), (+8, +9), (+1, +5), (-9, +9), (-15, 0)]
second = [(-5, -3), (0, -10), (+6, -5), (+6, 0), (+8, 5), (+1, +5), (-3, +2), (-10, 0)]
third = [(-10, -6), (0, -20), (+12, -10), (+12, 0), (+16, 10), (+2, +10), (-6, +4), (-20, 0)]


def mean_lot(lot):
    sum_x=0
    sum_y=0
    for elem in lot:
        sum_x += elem[0]
        sum_y += elem[1]
    print(f'({sum_x/len(lot)},{sum_y/len(lot)})')

mean_lot(first)
mean_lot(second)
mean_lot(third)
