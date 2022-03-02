##def f(a):
##    b = a+1
##    print(a, b)
##    print(locals())
##    print(globals())
##
##f(0)


from tkinter import *

class Calc:
    def enter(self, label):
        entry = self.entry
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
    def __init__(self):
        self.win = Tk()
        self.win.title('Calculator')
        self.entry = Entry(self.win, width=12, justify=RIGHT)
        self.entry.insert(0, '0')
        self.entry.pack()
        frm = Frame(self.win)
        frm.pack()
        for n in '10CDP':
            btn = Button(frm, text=n, width=3, command=(lambda char = n: self.enter(char)))
            btn.pack(side=LEFT)
        self.win.mainloop()    


if __name__ == "__main__":
    c = Calc()

    

