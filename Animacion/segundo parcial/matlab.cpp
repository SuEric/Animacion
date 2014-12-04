#include <iostream>
using namespace std;
// Metodo de newton


/* ALGORITMO ORIGINAL
 
 Si (f (P0) ≠ 0) AND (f ′(P0) ̸= 0)
 REPEAT
 Se hace P1 = P0
 Se hace P0 = P0 − f(P0)/f′(P0).
 UNTIL (|P0 − P1| < TOL1)OR(|f (P0)| < TOL2).

*/

// JONATHAN

/*
 xmin = handles.edit3;
 xmax = handles.edit4;
 ns = handles.edit5;
 p0 = handles.edit1;
 
 syms('x');
 
 fx=x^3-25;
 
 
 ejex2 = linspace(xmin,xmax,ns);
 x = ejex2;
 
 y = eval(fx);
 plot(ejex2, y);
 
 x = p0;
 p1 = p0;
 ev = eval(derivada);
 
 derivada = diff(fx);
 evdev = eval(derivada);
 p0 = p0 - (ev/evdev);
 
 if (ev != 0 && evdev != 0)
    while( abs(p0-p1) < tol || abs(ev) < tol)
        p1 = p0;
        x = p0;
        ev = eval(fx);
        evdev = eval(derivada);
        p0 = p0 - (ev/evdev);
    end
 end
 
 set(handles.text8,'String',num2str(p0));
 
 
 hold on;
 v=axis;
 line([p0,p0]',[v(3),v(4)]','LineWidth',1,'color','r');
 hold off;
 [30/09/13 00:05:47] SuEric: x^2 + 4x + 11;
 */

int main(int argc, char **argv)
{
    cout << "AHI LO TIENES :D" << endl;
    return 0;
}

