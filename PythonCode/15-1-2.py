from tkinter import *

class Calc(Frame):
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
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self.entry = Entry(self, width=12, justify=RIGHT)
        self.entry.insert(0, '0')
        self.entry.pack()
        for n in '10CDP':
            btn = Button(self, text=n, width=3, command=(lambda char = n: self.enter(char)))
            btn.pack(side=LEFT)


if __name__ == "__main__":
    win = Tk()
    win.title("Calculator")
    calc = Calc(win)
    calc.pack()
    win.mainloop()

    

