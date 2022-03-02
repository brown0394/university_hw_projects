module Effect_piezo(piezoout,bomb,defused,clk,rst,u10,LSB,sec,mute);

output piezoout;
input bomb;
input defused;
input clk;
input rst;
input u10;
input LSB;
input sec;
input mute;

wire  w0;
wire  w7;
wire  w8;
wire  w6;
wire  w10;
wire  w11;
wire  w12;
wire  w13;
wire  w14;
wire  w17;
wire  w18;
wire  w19;
wire  w20;
wire  w21;
wire  w23;
wire  w22;
wire  w25;
wire  w24;
wire  w26;
wire  w15;
wire  w27;
wire  w28;
wire  w29;

assign piezoout = w25;
assign w6 = bomb;
assign w10 = defused;
assign w18 = clk;
assign w19 = rst;
assign w28 = u10;
assign w8 = LSB;
assign w27 = sec;
assign w24 = mute;

piezo_bomb
     s2 (
      .bomb(w6),
      .clk(w18),
      .rst(w19),
      .pizo(w20));

pizeoDefused
     s1 (
      .bomb(w10),
      .clk(w18),
      .rst(w19),
      .pizo(w21));

PNU_CLK_DIV
     #(
      .cnt_num(318))
     s32 (
      .en(w13),
      .clk(w18),
      .rst(w19),
      .div_clk(w22));

PNU_NOT
     s3 (
      .o1(w7),
      .i1(w28));

PNU_AND3
     s4 (
      .i1(w7),
      .i2(w8),
      .o1(w14),
      .i3(w27));

PNU_AND2
     s5 (
      .i1(w11),
      .i2(w12),
      .o1(w15));

PNU_NOT
     s6 (
      .i1(w6),
      .o1(w11));

PNU_NOT
     s7 (
      .i1(w10),
      .o1(w12));

PNU_AND2
     s8 (
      .o1(w13),
      .i2(w14),
      .i1(w15));

PNU_CLK_DIV
     #(
      .cnt_num(318))
     s9 (
      .en(w17),
      .clk(w18),
      .rst(w19),
      .div_clk(w23));

PNU_AND2
     s10 (
      .o1(w17),
      .i2(w15),
      .i1(w29));

PNU_OR4
     s11 (
      .o1(w0),
      .i1(w20),
      .i2(w21),
      .i4(w23),
      .i3(w22));

PNU_AND2
     s13 (
      .i2(w0),
      .o1(w25),
      .i1(w26));

PNU_NOT
     s12 (
      .i1(w24),
      .o1(w26));

PNU_AND2
     s14 (
      .i1(w27),
      .i2(w28),
      .o1(w29));

endmodule

