module InputSelector(K1,K2,K3,K4,out);

input K1;
input K2;
input K3;
input K4;
output [7:0] out;

wire [7:0] b4;
wire  b4_6_w4;
wire  b4_0_w5;
wire  b4_3_w6;
wire  b4_7_w7;
wire  b4_1;
wire  b4_2;
wire  b4_4;
wire  b4_5;

assign out = b4;

assign b4[7] = K4;
assign b4[6] = K1;
assign b4[5] = b4_5;
assign b4[4] = b4_4;
assign b4[3] = K3;
assign b4[2] = b4_2;
assign b4[1] = b4_1;
assign b4[0] = K2;

assign b4_6_w4 = {b4[6]};
assign b4_0_w5 = {b4[0]};
assign b4_3_w6 = {b4[3]};
assign b4_7_w7 = {b4[7]};

PNU_OR4
     s0 (
      .i1(b4_6_w4),
      .i2(b4_0_w5),
      .i3(b4_3_w6),
      .i4(b4_7_w7),
      .o1(b4_5));

PNU_OR2
     s1 (
      .i1(b4_3_w6),
      .i2(b4_7_w7),
      .o1(b4_4));

PNU_OR2
     s2 (
      .i1(b4_0_w5),
      .i2(b4_7_w7),
      .o1(b4_2));

PNU_OR2
     s3 (
      .i1(b4_3_w6),
      .i2(b4_7_w7),
      .o1(b4_1));

endmodule

