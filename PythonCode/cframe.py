from tkinter import *

class MyCalc(Frame):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.operatorprs = False
        self.equalprs = False
        self.val = ""
        self.opval = ""
        
        self.entry = Entry(self, width=12, justify=RIGHT)
        self.entry.insert(0, '0')
        self.entry.pack()

        i = 0
        j = 0
        frm = Frame(self)
        frm.pack()
        for n in '789456123C0*+-=':
            btn = Button(frm, text=n, width=3, command=(lambda char=n: self.enter(char)))
            btn.grid(row=i, column=j)
            j = (j + 1) % 3
            if j == 0:
                i += 1
                
    def enter(self, label):
        entry = self.entry
        temp = ""
        if label == 'C':
            entry.delete(0, END)
            entry.insert(0, '0')
            self.val = ""
            self.opval = ""
            self.operatorprs = False
        elif label in '+-*':
            self.val = entry.get()
            self.opval = f" {label} "
            self.operatorprs = True
        elif label == '=':
            if self.val != "" and self.operatorprs is False:
                if self.equalprs:
                    temp = entry.get()
                    temp += self.opval
                    entry.delete(0, END)
                    entry.insert(0, eval(temp))
                else:
                    temp = entry.get()
                    self.opval += temp
                    self.val += self.opval
                    entry.delete(0, END)
                    entry.insert(0, eval(self.val))
                self.equalprs = True
            else:
                self.opval = ""
        else:
            if entry.get() == '0':
                entry.delete(0, END)
            if self.operatorprs:
                entry.delete(0, END)
                self.operatorprs = False
            if self.equalprs:
                self.entry.delete(0, END)
                self.equalprs = False
            entry.insert(END, label)


def main():   
    win = Tk()
    win.title('Calculator')
    calc = MyCalc(win)
    calc.pack()
    win.mainloop()

def forneospa():
    valin = input()
    print(eval(valin))

if __name__ == "__main__":
##    main()
    forneospa()
