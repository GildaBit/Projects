op_codes = {
    '100011': 'lw',
    '101011': 'sw',
    '000100': 'beq',
    '000101': 'bne'
}

func_codes = {
    '100000': 'add',
    '100010': 'sub',
    '100100': 'and',
    '100101': 'or',
    '101010': 'slt'
}

registers = {
    '00000': '$zero',
    '01001': '$t1',
    '01010': '$t2',
    '01011': '$t3',
    '01100': '$t4',
    '01101': '$t5',
    '01110': '$t6',
    '01111': '$t7',
    '10000': '$s0',
    '10001': '$s1',
    '10010': '$s2',
    '10011': '$s3',
    '10100': '$s4',
    '10101': '$s5',
    '10110': '$s6',
    '10111': '$s7'
}

def disassemble_from_mhc_file(mhc_file_path, asm_file_path):
    asm_file = open(asm_file_path, 'w')
    mhc_file = open(mhc_file_path, 'rb')
    output = ""
    for byte in mhc_file.read():
        bin_byte = '{0:08b}'.format(byte)
        output += bin_byte
    output = disassemble_bin(output)
    asm_file.write(output)

def disassemble_from_bin_file(bin_file_path, asm_file_path):
    bin_file = open(bin_file_path, 'r')
    bin_str = bin_file.read()
    final_output = ""
    while(len(bin_str) != 0):
        curr_str = bin_str[0:32]
        bin_str = bin_str[32:len(bin_str)]
        op_code = curr_str[0:6]
        if(op_code == "000000"):
            function = func_codes[curr_str[26:32]]
            rd = registers[curr_str[6:11]]
            rs = registers[curr_str[11:16]]
            rt = registers[curr_str[16:21]]
            final_output += f"{function} {rd}, {rs}, {rt}\n"
        elif op_code in op_codes:
            operation = op_codes[op_code]
            if op_code in ['100011', '101011']:
                rs = registers[curr_str[6:11]]
                rt = registers[curr_str[11:16]]
                offset = int(curr_str[16:32], 2)
                final_output += f"{operation} {rt}, {offset}({rs})\n"
            elif op_code in ['000100', '000101']:
                rs = registers[curr_str[6:11]]
                rt = registers[curr_str[11:16]]
                offset = int(curr_str[16:32], 2)
                final_output += f"{operation} {rs}, {rt}, {offset}\n"
    return final_output


def disassemble_bin(bin_str):
    final_output = ""
    while(len(bin_str) != 0):
        curr_str = bin_str[0:32]
        bin_str = bin_str[32:len(bin_str)]
        op_code = curr_str[0:6]
        if(op_code == "000000"):
            function = func_codes[curr_str[26:32]]
            rd = registers[curr_str[6:11]]
            rs = registers[curr_str[11:16]]
            rt = registers[curr_str[16:21]]
            final_output += f"{function} {rd}, {rs}, {rt}\n"
        elif op_code in op_codes:
            operation = op_codes[op_code]
            if op_code in ['100011', '101011']:
                rs = registers[curr_str[6:11]]
                rt = registers[curr_str[11:16]]
                offset = int(curr_str[16:32], 2)
                final_output += f"{operation} {rt}, {offset}({rs})\n"
            elif op_code in ['000100', '000101']:
                rs = registers[curr_str[6:11]]
                rt = registers[curr_str[11:16]]
                offset = int(curr_str[16:32], 2)
                final_output += f"{operation} {rs}, {rt}, {offset}\n"
    return final_output

disassemble_from_mhc_file("C:\\Users\\bitto\\OneDrive\\Desktop\\REPOSITORY\\CS240\\assignment_3\\program.mhc", "C:\\Users\\bitto\\OneDrive\\Desktop\\REPOSITORY\\CS240\\assignment_3\\program.asm")
