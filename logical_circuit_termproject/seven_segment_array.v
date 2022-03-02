module seven_segment_array(Out,A,B,C,D);

output [7:0] Out;
input A;
input B;
input C;
input D;

wire [7:0] b0;
wire  w12;
wire  w13;
wire  w16;
wire  w21;
wire  w24;
wire  w26;
wire  w31;
wire  w32;
wire  w19;
wire  w34;
wire  w33;
wire  w30;
wire  w36;
wire  w37;
wire  w38;
wire  w39;
wire  w41;
wire  w27;
wire  w35;
wire  w42;
wire  b0_0;
wire  b0_1;
wire  b0_2;
wire  b0_7;
wire  b0_6;
wire  b0_5;
wire  b0_4;
wire  b0_3;

assign Out = b0;
assign w30 = A;
assign w32 = B;
assign w35 = C;
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
      .i1(w35));

PNU_NOT
     s2 (
      .i1(w19),
      .o1(w27));

PNU_AND2
     s3 (
      .o1(w12),
      .i1(w32),
      .i2(w27));

PNU_XOR2
     s4 (
      .o1(w13),
      .i1(w32),
      .i2(w35));

PNU_AND2
     s5 (
      .o1(w16),
      .i1(w31),
      .i2(w27));

PNU_OR3
     s6 (
      .i2(w12),
      .i3(w13),
      .i1(w30),
      .o1(b0_1));

PNU_OR3
     s7 (
      .i3(w16),
      .i1(w32),
      .i2(w30),
      .o1(b0_2));

PNU_XNOR2
     s8 (
      .o1(w21),
      .i1(w32),
      .i2(w19));

PNU_OR3
     s9 (
      .i1(w21),
      .i2(w30),
      .i3(w35),
      .o1(b0_7));

PNU_XNOR2
     s10 (
      .o1(w24),
      .i2(w19),
      .i1(w35));

PNU_OR3
     s11 (
      .i1(w24),
      .i2(w30),
      .i3(w41),
      .o1(b0_6));

PNU_OR2
     s12 (
      .o1(w26),
      .i1(w41),
      .i2(w35));

PNU_AND2
     s13 (
      .i2(w26),
      .i1(w27),
      .o1(b0_3));

PNU_ZERO
     s14 (
      .o1(b0_0));

PNU_OR2
     s15 (
      .i2(w31),
      .o1(w33),
      .i1(w30));

PNU_XNOR2
     s16 (
      .i1(w32),
      .i2(w19),
      .o1(w34));

PNU_AND2
     s17 (
      .i2(w34),
      .i1(w33),
      .o1(w38));

PNU_OR2
     s18 (
      .o1(w36),
      .i1(w41),
      .i2(w27));

PNU_XOR2
     s19 (
      .i1(w30),
      .o1(w37),
      .i2(w35));

PNU_AND2
     s20 (
      .i1(w36),
      .i2(w37),
      .o1(w39));

PNU_OR2
     s21 (
      .i1(w38),
      .i2(w39),
      .o1(b0_4));

PNU_AND3
     s22 (
      .i1(w41),
      .i3(w27),
      .i2(w35),
      .o1(w42));

PNU_NOT
     s23 (
      .i1(w42),
      .o1(b0_5));

endmodule

