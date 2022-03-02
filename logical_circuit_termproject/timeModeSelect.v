module timeModeSelect(tripl,hept,mod,out);

input [1:0] tripl;
input [2:0] hept;
input mod;
output [2:0] out;

wire [2:0] b10;
wire [1:0] b12;
wire  w13;
wire [2:0] b9;
wire  w17;
wire  w18;
wire  w19;
wire  w20;
wire  w23;
wire  b10_2_w9;
wire  b10_1_w14;
wire  b10_0_w15;
wire  b12_0_w11;
wire  b12_1_w10;
wire  b9_2;
wire  b9_1;
wire  b9_0;

assign b12 = tripl;
assign b10 = hept;
assign w13 = mod;
assign out = b9;

assign b9[2] = b9_2;
assign b9[1] = b9_1;
assign b9[0] = b9_0;

assign b10_2_w9 = {b10[2]};
assign b10_1_w14 = {b10[1]};
assign b10_0_w15 = {b10[0]};
assign b12_0_w11 = {b12[0]};
assign b12_1_w10 = {b12[1]};

PNU_AND2
     s1 (
      .i1(b10_2_w9),
      .o1(b9_2),
      .i2(w23));

PNU_AND2
     s2 (
      .i1(b10_1_w14),
      .o1(w17),
      .i2(w23));

PNU_AND2
     s3 (
      .i1(b10_0_w15),
      .o1(w18),
      .i2(w23));

PNU_AND2
     s5 (
      .i2(w13),
      .i1(b12_1_w10),
      .o1(w19));

PNU_AND2
     s6 (
      .i2(w13),
      .i1(b12_0_w11),
      .o1(w20));

PNU_OR2
     s7 (
      .i1(w17),
      .i2(w19),
      .o1(b9_1));

PNU_OR2
     s8 (
      .i1(w18),
      .i2(w20),
      .o1(b9_0));

PNU_NOT
     s9 (
      .i1(w13),
      .o1(w23));

endmodule

