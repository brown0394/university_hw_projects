from tkinter import *

operatorprs = False
equalprs = False
val = ""
opval = ""


def enter(label):
    global operatorprs
    global val
    global opval
    global equalprs
    temp = ""

    if label == 'C':
        entry.delete(0, END)
        entry.insert(0, '0')
        val = ""
        opval = ""
        operatorprs = False
    elif label in '+-*':
        val = entry.get()
        opval = f" {label} "
        operatorprs = True
    elif label == '=':
        if val != "" and operatorprs is False:
            if equalprs:
                temp = entry.get()
                temp += opval
                entry.delete(0, END)
                entry.insert(0, eval(temp))
            else:
                temp = entry.get()
                opval += temp
                val += opval
                entry.delete(0, END)
                entry.insert(0, eval(val))
            equalprs = True
        else:
            opval = ""
    else:
        if entry.get() == '0':
            entry.delete(0, END)
        if operatorprs:
            entry.delete(0, END)
            operatorprs = False
        if equalprs:
            entry.delete(0, END)
            equalprs = False
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

    i = 0
    j = 0
    for n in '789456123C0*+-=':
        btn = Button(frm, text=n, width=3, command=(lambda char=n: enter(char)))
        btn.grid(row=i, column=j)
        j = (j + 1) % 3
        if j == 0:
            i += 1
    win.mainloop()

def forneospa():
    valin = input()
    print(eval(valin))

if __name__ == "__main__":
    main()
    forneospa()
