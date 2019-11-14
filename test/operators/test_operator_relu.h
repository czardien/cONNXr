#ifndef TEST_OPERATOR_RELU_H
#define TEST_OPERATOR_RELU_H
#include "common_operators.h"
#include "../../src/operators/relu.h"

void test_operator_relu(void)
{
  Onnx__TensorProto *inp0 = openTensorProtoFile("../test/node/test_relu/test_data_set_0/input_0.pb");
  Onnx__TensorProto *out0 = openTensorProtoFile("../test/node/test_relu/test_data_set_0/output_0.pb");

  // Tensors have raw_data. Parse it and store into a normal field for the sake of simplicity
  convertRawDataOfTensorProto(inp0);
  convertRawDataOfTensorProto(out0);

  Onnx__TensorProto *result = malloc (sizeof(*result));
  operator_relu(inp0, result);

  compareAlmostEqualTensorProto(result, out0);
}

#endif