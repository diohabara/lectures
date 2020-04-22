module alu(A,
           B,
           O,
           CTR,
           ck);
    input	[7:0]	A, B;
    input	[3:0]	CTR;
    input	ck;
    output	[7:0] O;
    reg	[7:0]	INA, INB, O;
    reg	[3:0]	C;
    wire	[7:0]	OUT;
    always @(posedge ck) begin
        C   <= CTR;
        INA <= A;
        INB <= B;
        O   <= OUT;
    end
    always @(C || INA || INB) begin
        case (C)
            'b0000 : O <= A + B;
            'b0001 : O <= A - B;
            'b1000 : O <= A & B;
            'b1001 : O <= A | B;
            'b1010 : O <= A ^ B;
            'b1010 : O <= ~A;
            'b1011 : O <= A >> 1;
            'b1100 : O <= A << 1;
            'b1101 : O <= {A[0], A[7:1]};
            'b1111 : O <= {A[6:0], A[7]};
        endcase
    end
endmodule
