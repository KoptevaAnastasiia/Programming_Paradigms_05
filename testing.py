import subprocess

def audit(input_data):


    process = subprocess.Popen(

        ['./test01'],

        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True

    )

    output_t, error_t = process.communicate(input_data)
    return output_t , error_t 





def testing():
    tests = [
        {"input": "2+300\n", "expected_output": "Result: 302"},
        {"input": "10-4*0\n", "expected_output": "Result: 10"},
        {"input": "3*1-1\n", "expected_output": "Result: 2"},
        {"input": "8/2\n", "expected_output": "Result: 4"},
        {"input": "min(4,9)\n", "expected_output": "min:4"},
        {"input": "max(4,9)\n", "expected_output": "max:9"}
    ]

    for i in tests:
        input_data = i["input"]
        expected_output = i["expected_output"]

        output, error = audit(input_data)


        if expected_output not in output:
            print(f"incorrectly for: {input_data}. Need: {expected_output}, but we get: {output}")

        else:
            print(f"correctlyfor for: {input_data}")

testing()
