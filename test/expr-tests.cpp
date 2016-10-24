#include "test.h"
#include "test_tensors.h"

#include "tensor.h"
#include "var.h"
#include "expr.h"
#include "packed_tensor.h"
#include "operator.h"

using namespace taco;

struct TestData {
  TestData(Tensor<double> tensor, const vector<Var> indexVars, Expr expr,
          PackedTensor::Indices expectedIndices, vector<double> expectedValues)
      : tensor(tensor),
        expectedIndices(expectedIndices), expectedValues(expectedValues) {
    tensor(indexVars) = expr;
  }

  Tensor<double>        tensor;
  PackedTensor::Indices expectedIndices;
  vector<double>        expectedValues;
};

static ostream &operator<<(ostream& os, const TestData& data) {
  os << data.tensor.getName() << ": "
     << util::join(data.tensor.getDimensions(), "x")
     << " (" << data.tensor.getFormat() << ")";
  return os;
}

struct expr : public TestWithParam<TestData> {};

TEST_P(expr, eval) {
  Tensor<double> tensor = GetParam().tensor;

  tensor.printIterationSpace();

//  tensor.compile();
//  tensor.assemble();
//  tensor.evaluate();
//
//  auto tensorPack = tensor.getPackedTensor();
//  ASSERT_NE(nullptr, tensorPack);
//
//  // Check that the indices are as expected
//  auto& expectedIndices = GetParam().expectedIndices;
//  auto&         indices = tensorPack->getIndices();
//  ASSERT_EQ(expectedIndices.size(), indices.size());
//
//  for (size_t i=0; i < indices.size(); ++i) {
//    auto expectedIndex = expectedIndices[i];
//    auto         index = indices[i];
//    ASSERT_EQ(expectedIndex.size(), index.size());
//    for (size_t j=0; j < index.size(); ++j) {
//      ASSERT_VECTOR_EQ(expectedIndex[j], index[j]);
//    }
//  }
//
//  auto& expectedValues = GetParam().expectedValues;
//  ASSERT_EQ(expectedValues.size(), tensorPack->getNnz());
//  auto values = tensorPack->getValues();
//  ASSERT_VECTOR_EQ(expectedValues, values);
}

Var i("i"), j("j"), k("k"), l("l");

INSTANTIATE_TEST_CASE_P(vector_neg, expr,
    Values(TestData(Tensor<double>("a",{5},Format({Dense})),
                    {i},
                    -d5a("b",Format({Dense}))(i),
                    {
                      {
                        // Dense index
                      }
                    },
                    {0.0, -1.0, 0.0, 0.0, -2.0}
                    ),
           TestData(Tensor<double>("a",{5},Format({Sparse})),
                    {i},
                    -d5a("b",Format({Sparse}))(i),
                    {
                      {
                        // Sparse index
                        {0,2},
                        {1,4}
                      },
                    },
                    {-1, -2}
                    )
           )
);

INSTANTIATE_TEST_CASE_P(matrix_neg, expr,
    Values(TestData(Tensor<double>("aa",{3,3},Format({Dense,Dense})),
                    {i,j},
                    -d33a("bb",Format({Dense,Dense}))(i,j),
                    {
                      {
                        // Dense index
                      },
                      {
                        // Dense index
                      }
                    },
                    { 0, -1,  0,
                      0,  0,  0,
                     -2,  0, -3}
                    )/*,
           TestData(Tensor<double>("a",{3,3},Format({Dense,Sparse})),
                    {i,j},
                    -d33a("b",Format({Dense,Sparse}))(i,j),
                    {
                      {
                        // Dense index
                      },
                      {
                        {0,1,1,3},
                        {1,0,2}
                      }
                    },
                    { 0, -1,  0,
                      0,  0,  0,
                     -2,  0, -3}
                    )*/
           )
);
//
//INSTANTIATE_TEST_CASE_P(DISABLED_vector_add, expr,
//    Values(TestData(Tensor<double>("a",{5},Format({Dense})),
//                    {i},
//                    d5a("b",Format({Dense}))(i) +
//                    d5b("c",Format({Dense}))(i),
//                    {
//                      {
//                        // Dense index
//                      }
//                    },
//                    {0.0, -1.0, 0.0, 0.0, -2.0}
//                    )
//           )
//);
//
//INSTANTIATE_TEST_CASE_P(DISABLED_matrix_add, expr,
//  Values(TestData(Tensor<double>("A",{3,3},Format({Dense,Dense})),
//                  {i,j},
//                  d33a("b",Format({Dense,Dense}))(i,j) +
//                  d33b("c",Format({Dense,Dense}))(i,j),
//                  {
//                    {
//                      // Dense index
//                    },
//                    {
//                      // Dense index
//                    }
//                  },
//                  { 0, -1,  0,
//                    0,  0,  0,
//                   -2,  0, -3}
//                  )
//         )
//);
