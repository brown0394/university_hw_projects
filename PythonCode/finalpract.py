from tkinter import *



def main():
    window = Tk()
    window.title('Practice')
    frm1 = Frame(window)
    frm1.pack()
    lab = Label(frm1, text="HOOOO")
    lab.pack()
    btn = Button(frm1, text = "BUU")
    btn.pack()
    

if __name__ == "__main__":
    main()
