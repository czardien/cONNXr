#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "trace.h"
#include "utils.h"

operator_status operator__onnx__batchnormalization__9__T_tensor_float(
    node_context *ctx
)
{
  TRACE_LEVEL0("Calling operator_batchnormalization\n");


  Onnx__TensorProto *X = searchInputByName(ctx, 0);
  Onnx__TensorProto *scale = searchInputByName(ctx, 1);
  Onnx__TensorProto *B = searchInputByName(ctx, 2);
  Onnx__TensorProto *mean = searchInputByName(ctx, 3);
  Onnx__TensorProto *var = searchInputByName(ctx, 4);

  Onnx__TensorProto *Y = searchOutputByName(ctx, 0);

  /* TODO: Not implemented
  Onnx__TensorProto *mean = searchOutputByName(ctx, 1);
  Onnx__TensorProto *var = searchOutputByName(ctx, 2);
  Onnx__TensorProto *saved_mean = searchOutputByName(ctx, 3);
  Onnx__TensorProto *saved_var = searchOutputByName(ctx, 4);*/

  if (0){
    /* TODO: Check some conditions. For example if a specific
     * functionality is not supported */
    return 1;
  }

  //Onnx__AttributeProto *momentumAttr = searchAttributeNyName(n_attribute, attribute, "momentum");
  debug_print_attributes(ctx->onnx_node->n_attribute,ctx->onnx_node->attribute);
  /* Epsilon is hardcoded to float */
  float eps = 0.00001; /* Default value */

  if (ctx->onnx_node->n_attribute == 1){
    eps =ctx->onnx_node->attribute[0]->f;
  }

  // Allocte memory
  Y->dims = malloc(X->n_dims * sizeof(int64_t));
  Y->n_dims = X->n_dims;
  for(int i = 0; i < Y->n_dims; i++){
    Y->dims[i] = X->dims[i];
  }

  Y->has_raw_data = 0;

  // TODO
  Y->data_type = X->data_type;

  Y->data_type = ONNX__TENSOR_PROTO__DATA_TYPE__FLOAT;
  Y->n_float_data = X->n_float_data;
  Y->float_data = malloc(Y->n_float_data * sizeof(float));
  for (int i = 0; i < Y->n_float_data; i++) {
    int index = (i/(X->dims[2] * X->dims[3])) % X->dims[1];
    //TRACE_LEVEL0("input=%f\n", X->float_data[i]);
    //TRACE_LEVEL0("index=%dmean=%f, var=%f, scale=%f, B=%f\n", index, mean, var, scale, B);
    Y->float_data[i] = (X->float_data[i] - mean->float_data[index]) / sqrtf(var->float_data[index] + eps);
    Y->float_data[i] = scale->float_data[index] * Y->float_data[i] + B->float_data[index];
  }

  return 0;
}
