module InputSelectorMod2(K1,K2,K3,K4,K5,out);

input K1;
input K2;
input K3;
input K4;
input K5;
output [7:0] out;

wire [7:0] b15;
wire  w17;
wire  w16;
wire  w15;
wire  w18;
wire  b15_7;
wire  b15_6;
wire  b15_5;
wire  b15_4;
wire  b15_1;
wire  b15_0;
wire  b15_3_w12;
wire  b15_2_w13;

assign w16 = K1;
assign w15 = K2;
assign w18 = K4;
assign out = b15;

assign b15[7] = b15_7;
assign b15[6] = b15_6;
assign b15[5] = b15_5;
assign b15[4] = b15_4;
assign b15[3] = K3;
assign b15[2] = K5;
assign b15[1] = b15_1;
assign b15[0] = b15_0;

assign b15_3_w12 = {b15[3]};
assign b15_2_w13 = {b15[2]};

PNU_OR2
     s0 (
      .o1(b15_7),
      .i1(b15_3_w12),
      .i2(w18));

PNU_OR2
     s1 (
      .o1(b15_6),
      .i1(w16),
      .i2(w18));

PNU_OR4
     s2 (
      .o1(b15_5),
      .i1(w16),
      .i2(b15_3_w12),
      .i3(w18),
      .i4(b15_2_w13));

PNU_OR3
     s3 (
      .o1(b15_4),
      .i1(w16),
      .i2(b15_3_w12),
      .i3(b15_2_w13));

PNU_OR4
     s4 (
      .i1(w17),
      .o1(b15_1),
      .i2(b15_3_w12),
      .i3(w18),
      .i4(b15_2_w13));

PNU_OR2
     s5 (
      .o1(w17),
      .i1(w16),
      .i2(w15));

PNU_OR4
     s6 (
      .o1(b15_0),
      .i1(w15),
      .i2(b15_3_w12),
      .i3(w18),
      .i4(b15_2_w13));

endmodule

