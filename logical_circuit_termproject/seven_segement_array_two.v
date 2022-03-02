module seven_segement_array_two(Out,B,C,D);

output [7:0] Out;
input B;
input C;
input D;

wire [7:0] b0;
wire  w12;
wire  w13;
wire  w26;
wire  w19;
wire  w34;
wire  w36;
wire  w38;
wire  w39;
wire  w27;
wire  w42;
wire  w32;
wire  w48;
wire  w49;
wire  w41;
wire  w50;
wire  w31;
wire  w25;
wire  b0_0;
wire  b0_2;
wire  b0_7;
wire  b0_6;
wire  b0_5;
wire  b0_4;
wire  b0_3;
wire  b0_1;

assign Out = b0;
assign w32 = B;
assign w25 = C;
assign w19 = D;

assign b0[7] = b0_7;
assign b0[6] = b0_6;
assign b0[5] = b0_5;
assign b0[4] = b0_4;
assign b0[3] = b0_3;
assign b0[2] = b0_2;
assign b0[1] = b0_1;
assign b0[0] = b0_0;

PNU_NOT
     s0 (
      .i1(w32),
      .o1(w41));

PNU_NOT
     s1 (
      .o1(w31),
      .i1(w25));

PNU_NOT
     s2 (
      .i1(w19),
      .o1(w27));

PNU_AND2
     s3 (
      .o1(w12),
      .i2(w27),
      .i1(w32));

PNU_XOR2
     s4 (
      .o1(w13),
      .i1(w32),
      .i2(w25));

PNU_AND2
     s5 (
      .i2(w27),
      .o1(w48),
      .i1(w31));

PNU_XNOR2
     s8 (
      .i2(w19),
      .i1(w32),
      .o1(w49));

PNU_XNOR2
     s10 (
      .i2(w19),
      .o1(w50),
      .i1(w25));

PNU_OR2
     s12 (
      .o1(w26),
      .i1(w41),
      .i2(w25));

PNU_AND2
     s13 (
      .i2(w26),
      .i1(w27),
      .o1(b0_3));

PNU_ZERO
     s14 (
      .o1(b0_0));

PNU_XNOR2
     s16 (
      .i2(w19),
      .o1(w34),
      .i1(w32));

PNU_AND2
     s17 (
      .i2(w34),
      .o1(w38),
      .i1(w31));

PNU_OR2
     s18 (
      .o1(w36),
      .i2(w27),
      .i1(w41));

PNU_AND2
     s20 (
      .i1(w36),
      .o1(w39),
      .i2(w25));

PNU_OR2
     s21 (
      .i1(w38),
      .i2(w39),
      .o1(b0_4));

PNU_AND3
     s22 (
      .i3(w27),
      .o1(w42),
      .i1(w41),
      .i2(w25));

PNU_NOT
     s23 (
      .i1(w42),
      .o1(b0_5));

PNU_OR2
     s24 (
      .i1(w12),
      .i2(w13),
      .o1(b0_1));

PNU_OR2
     s25 (
      .o1(b0_2),
      .i1(w32),
      .i2(w48));

PNU_OR2
     s26 (
      .o1(b0_7),
      .i1(w49),
      .i2(w25));

PNU_OR2
     s27 (
      .o1(b0_6),
      .i2(w41),
      .i1(w50));

endmodule

