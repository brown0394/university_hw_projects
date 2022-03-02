##def f(a):
##    b = a+1
##    print(a, b)
##    print(locals())
##    print(globals())
##
##f(0)

from tkinter import *

def enter(label):
    global entry
    if label == 'C':
        entry.delete(0, END)
        entry.insert(0, '0')
    elif label == 'D':
        ans = eval(entry.get())
        ans *= 2
        entry.delete(0, END)
        entry.insert(0, ans)
    elif label == 'P':
        ans = eval(entry.get())
        ans = ans ** 2
        entry.delete(0, END)
        entry.insert(0, ans)
    elif entry.get() == '0':
        entry.delete(0, END)
        entry.insert(END, label)
    else:
        entry.insert(END, label)


def main():
    global entry
    win = Tk()
    win.title('Calculator')
    entry = Entry(win, width=12, justify=RIGHT)
    entry.insert(0, '0')
    entry.pack()
    frm = Frame(win)
    frm.pack()
    for n in '10CDP':
        btn = Button(frm, text=n, width=3, command=(lambda char = n: enter(char)))
        btn.pack(side=LEFT)
    win.mainloop()    


if __name__ == "__main__":
    entry = None
    main()

    

