// Copyright 2009-2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#include "dnnl_device.h"
#include "dnnl_tensor.h"
#include "dnnl_conv.h"
#include "dnnl_pool.h"

namespace oidn {

  void DNNLDevice::wait()
  {
    dnnlStream.wait();
  }

  std::shared_ptr<Tensor> DNNLDevice::newTensor(const TensorDesc& desc)
  {
    return std::make_shared<DNNLTensor>(Ref<DNNLDevice>(this), desc);
  }

  std::shared_ptr<Tensor> DNNLDevice::newTensor(const TensorDesc& desc, void* data)
  {
    return std::make_shared<DNNLTensor>(Ref<DNNLDevice>(this), desc, data);
  }

  std::shared_ptr<Tensor> DNNLDevice::newTensor(const Ref<Buffer>& buffer, const TensorDesc& desc, size_t byteOffset)
  {
    assert(buffer->getDevice() == this);
    return std::make_shared<DNNLTensor>(buffer, desc, byteOffset);
  }

  std::shared_ptr<ConvNode> DNNLDevice::newConvNode(const ConvDesc& desc)
  {
    return std::make_shared<DNNLConvNode>(Ref<DNNLDevice>(this), desc);
  }

  std::shared_ptr<PoolNode> DNNLDevice::newPoolNode(const PoolDesc& desc)
  {
    return std::make_shared<DNNLPoolNode>(Ref<DNNLDevice>(this), desc);
  }

} // namespace oidn