unitsize(0.9cm);

real level_height = 1.1;
real circle_size = 0.38;
path circle = scale(circle_size) * unitcircle;
int total;
void draw_tree(int levels, real x1, real x2, real y, int id)
{
    real mov = (x2 - x1) / 2;
    pair node = (x1 + mov, y);
    if (id == 5 || id == 14)
        filldraw(shift(node) * circle, grey);
    else
        draw(shift(node) * circle);
    label((string)(total - id), node);
    if (levels > 1)
        for (int i = 0; i < 2; ++i)
        {
            pair son = (x1 + mov * (i + 0.5), y - level_height);
            path conn = node -- son;
            conn = cut(conn, shift(node) * circle, 1).after;
            conn = cut(conn, shift(son) * circle, 1).before;

            string lab = "";
            if (i == 0 && (id == 1 || id == 7)) lab = "L";
            if (i == 1 && (id == 1 || id == 3 || id == 2)) lab = "R";
            if (lab == "") draw(conn);
            else
            {
                draw(conn, Arrow);
                label(lab, conn);
            }
            draw_tree(levels - 1, x1 + mov * i, x1 + mov * (i + 1), y - level_height, id * 2 + i);
        }
}

int levels = 4;
total = 2 ^ levels;
draw_tree(levels, 0, total / 2, 0, 1);
