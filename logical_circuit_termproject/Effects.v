module Effects(bomb,defused,clk,rst,stepout,fLEDG,u10,fLEDR,mute);

input bomb;
input defused;
input clk;
input rst;
output [3:0] stepout;
output [3:0] fLEDG;
input u10;
output [3:0] fLEDR;
input mute;

wire [3:0] b26;
wire [3:0] b25;
wire [3:0] b39;
wire [3:0] b30;
wire [3:0] b31;
wire  w21;
wire  w22;
wire  w26;
wire  w30;
wire  w32;
wire  w27;
wire  w46;
wire  w47;
wire  w31;
wire  w33;
wire  w28;
wire  w29;
wire  w48;
wire  b26_3_w34;
wire  b25_3_w35;
wire  b26_2_w36;
wire  b25_2_w37;
wire  b26_1_w38;
wire  b25_1_w39;
wire  b26_0_w40;
wire  b25_0_w41;
wire  b39_3;
wire  b39_2;
wire  b39_1;
wire  b39_0;

assign w28 = bomb;
assign w30 = defused;
assign w26 = clk;
assign w29 = rst;
assign stepout = b39;
assign fLEDG = b30;
assign w21 = u10;
assign fLEDR = b31;
assign w47 = mute;

assign b39[3] = b39_3;
assign b39[2] = b39_2;
assign b39[1] = b39_1;
assign b39[0] = b39_0;

assign b26_3_w34 = {b26[3]};
assign b25_3_w35 = {b25[3]};
assign b26_2_w36 = {b26[2]};
assign b25_2_w37 = {b25[2]};
assign b26_1_w38 = {b26[1]};
assign b25_1_w39 = {b25[1]};
assign b26_0_w40 = {b26[0]};
assign b25_0_w41 = {b25[0]};

StepBomb
     s0 (
      .st(b26),
      .clk(w46),
      .rst(w29));

bombRed
     s3 (
      .red(b31),
      .in(w28));

defuseGreen
     s4 (
      .green(b30),
      .in(w30));

stMotor
     s13 (
      .st(b25),
      .clk(w32),
      .rst(w48));

PNU_OR2
     s16 (
      .i1(b26_3_w34),
      .i2(b25_3_w35),
      .o1(b39_3));

PNU_OR2
     s17 (
      .i1(b26_2_w36),
      .i2(b25_2_w37),
      .o1(b39_2));

PNU_OR2
     s18 (
      .i1(b26_1_w38),
      .i2(b25_1_w39),
      .o1(b39_1));

PNU_OR2
     s19 (
      .i1(b26_0_w40),
      .i2(b25_0_w41),
      .o1(b39_0));

PNU_NOT
     s9 (
      .o1(w22),
      .i1(w30));

PNU_AND2
     s12 (
      .i1(w26),
      .o1(w27),
      .i2(w28));

PNU_AND2
     s14 (
      .o1(w32),
      .i1(w31),
      .i2(w33));

PNU_AND2
     s15 (
      .i2(w27),
      .o1(w46),
      .i1(w31));

PNU_NOT
     s20 (
      .i1(w47),
      .o1(w31));

PNU_AND3
     s21 (
      .i2(w21),
      .i3(w22),
      .i1(w26),
      .o1(w33));

PNU_OR2
     s22 (
      .i2(w28),
      .i1(w29),
      .o1(w48));

endmodule

