module piezo_bomb(rst,pizo,bomb,clk);

input rst;
output pizo;
input bomb;
input clk;

wire  w0;
wire  w1;
wire  w2;
wire  w3;
wire  w9;
wire  w13;
wire  w16;
wire  w17;
wire  w18;
wire  w15;
wire  w19;
wire  w20;
wire  w21;
wire  w24;
wire  w25;
wire  w26;
wire  w27;
wire  w22;
wire  w29;
wire  w31;
wire  w23;
wire  w28;
wire  w32;
wire  w30;

assign w31 = rst;
assign pizo = w24;
assign w27 = bomb;
assign w23 = clk;

PNU_CLK_DIV
     #(
      .cnt_num(1275))
     s0 (
      .div_clk(w0),
      .rst(w31),
      .clk(w23),
      .en(w28));

PNU_MUX4
     s1 (
      .i1(w0),
      .i2(w1),
      .i3(w2),
      .i4(w3),
      .e1(w18),
      .e2(w15),
      .o1(w24));

PNU_CLK_DIV
     #(
      .cnt_num(1516))
     s2 (
      .div_clk(w1),
      .rst(w31),
      .clk(w23),
      .en(w28));

PNU_CLK_DIV
     #(
      .cnt_num(1912))
     s3 (
      .div_clk(w2),
      .rst(w31),
      .clk(w23),
      .en(w28));

PNU_CLK_DIV
     #(
      .cnt_num(2272))
     s4 (
      .div_clk(w3),
      .rst(w31),
      .clk(w23),
      .en(w28));

PNU_NOT
     s7 (
      .o1(w9),
      .i1(w18));

PNU_AND2
     s8 (
      .i1(w9),
      .o1(w17),
      .i2(w15));

PNU_NOT
     s10 (
      .o1(w13),
      .i1(w15));

PNU_AND2
     s11 (
      .i2(w13),
      .o1(w16),
      .i1(w18));

PNU_NOT
     s12 (
      .i1(w15),
      .o1(w22));

PNU_OR2
     s13 (
      .i2(w16),
      .i1(w17),
      .o1(w29));

PNU_AND2
     s15 (
      .i1(w19),
      .i2(w20),
      .o1(w21));

PNU_NOT
     s16 (
      .i1(w18),
      .o1(w19));

PNU_NOT
     s17 (
      .i1(w15),
      .o1(w20));

isisfirst
     s18 (
      .clk(w21),
      .out(w25),
      .rst(w31));

PNU_NOT
     s20 (
      .i1(w25),
      .o1(w26));

PNU_AND2
     s19 (
      .i2(w26),
      .i1(w27),
      .o1(w28));

ClockDivFive
     s21 (
      .rst(w31),
      .clk(w23),
      .out(w32));

PNU_DFF
     s22 (
      .Q(w18),
      .D(w29),
      .reset(w31),
      .clock(w30));

PNU_DFF
     s23 (
      .Q(w15),
      .D(w22),
      .reset(w31),
      .clock(w30));

PNU_AND2
     s24 (
      .i2(w28),
      .i1(w32),
      .o1(w30));

endmodule

