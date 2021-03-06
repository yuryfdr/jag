/*
 *
 * This file is part of JAG, Puzzle game where the goal is to break all
 * the target pieces in each level and do this before the time runs out.
 *
 * Many thanks to XlabSoft & Ind. Infosystems, the originals authors of JAG.
 *
 * Copyright holder 2009-2012 Developed by XlabSoft & Industrial Infosystems
 * Work continued by 2017 Carlos Donizete Froes [a.k.a coringao]
 *
 * JAG is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * JAG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with JAG. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef SCALER_H
#define SCALER_H

#define DX(v)   (scaler->dx(v))
#define DY(v)   (scaler->dy(v))

#define X56  (scaler->x56())
#define Y56  (scaler->y56())

#define X48  (scaler->x48())
#define Y48  (scaler->y48())

#define X100  (scaler->x100())
#define X900  (scaler->x900())
#define X910  (scaler->x910())

#define Y20  (scaler->y20())

#define WIDTH  (scaler->width())
#define HEIGHT  (scaler->height())

#define RIGHT(v)   (scaler->right(v))
#define BOTTOM(v)  (scaler->bottom(v))

#define LEFT_CENTER(v, target)  (((target)-(v))/2)

class Scaler
{
public:
    Scaler();

    static void init();

    void rescale(int w, int h);

    inline int dx(int val) const        { return (int)(cw*val); }
    inline int dy(int val) const        { return (int)(ch*val); }

    inline int right(int val) const     { return win_w-val; }
    inline int bottom(int val) const    { return win_h-val; }

    inline int x56() const              { return m_x56; }
    inline int y56() const              { return m_y56; }

    inline int x48() const              { return m_x48; }
    inline int y48() const              { return m_y48; }

    inline int x100() const              { return m_x100; }
    inline int x900() const              { return m_x900; }
    inline int x910() const              { return m_x910; }

    inline int y20() const              { return m_y20; }

    inline int width() const              { return win_w; }
    inline int height() const              { return win_h; }

private:
    float cw, ch;

    int m_x56, m_y56;
    int m_x48, m_y48;
    int m_x100, m_x900, m_x910, m_y20;
    int win_w, win_h;
};

extern Scaler *scaler;

#endif // SCALER_H
