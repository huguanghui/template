import yaml
import caffe
import numpy as np

def quantize_inverse(data, bw, fl):
    qdata = np.zeros(data.size, np.float64)
    data32 = data.reshape(data.size)
    max_data = np.float64((pow(2, bw - 1) - 1) * pow(2, float(-fl)))
    min_data = np.float64(-pow(2, bw - 1) * pow(2, float(-fl)))
    for i in range(0, data32.size):
        d = data32[i]
        d = max(min(d, max_data), min_data)
        d = round(d / pow(2.0, -fl))
        d = d * pow(2.0, -fl)
        qdata[i] = d

    return qdata

class BroadcastSum(caffe.Layer):
    def setup(self, bottom, top):
        params = yaml.load(self.param_str)
        self.axis = params["axis"]

        self.shape_0 = list(bottom[0].data.shape)
        self.shape_1 = list(bottom[1].data.shape)


    def reshape(self, bottom, top):
        self.shape_0 = list(bottom[0].data.shape)
        self.shape_1 = list(bottom[1].data.shape)
        if len(self.shape_0) > len(self.shape_1):
            top[0].reshape(*self.shape_0)
        elif len(self.shape_0) < len(self.shape_1):
            top[0].reshape(*self.shape_1)
        elif self.shape_0[self.axis] > self.shape_1[self.axis]:
            top[0].reshape(*self.shape_0)
        else:
            top[0].reshape(*self.shape_1)
        
        top[1].reshape(*self.shape_1)

    def forward(self, bottom, top):
        shape_0, shape_1 = self.shape_0.copy(), self.shape_1.copy()
        if len(shape_0) < len(shape_1):
            shape_0.insert(self.axis, 1)
        elif len(shape_0) > len(shape_1):
            shape_1.insert(self.axis, 1)
        else:
            s_0, s_1 = shape_0[self.axis], shape_1[self.axis]
            assert max(s_0, s_1) % s_0 == 0 and max(s_0, s_1) % s_1 == 0
        top[0].data[...] = bottom[0].data.reshape(*shape_0) + bottom[1].data.reshape(*shape_1)

    def backward(self, top, propagate_down, bottom):
        pass


class ReductionSum(caffe.Layer):
    def setup(self, bottom, top):
        params = yaml.load(self.param_str)
        self.axis = params["axis"]
        self.keep_dims = params["keep_dims"]

    def reshape(self, bottom, top):
        if self.keep_dims:
            shape = list(bottom[0].data.shape)
            shape[self.axis] = 1
        else:
            shape = [s for i, s in enumerate(bottom[0].data.shape) if i != self.axis]
        top[0].reshape(*shape)

    def forward(self, bottom, top):
        top[0].data[...] = bottom[0].data.sum(axis=self.axis, keepdims=self.keep_dims)

    def backward(self, top, propagate_down, bottom):
        pass


class AxPyLayer(caffe.Layer):
    def setup(self, bottom, top):
        params = yaml.load(self.param_str)
        self.alpha = params['alpha']
        self.beta = params['beta']

    def reshape(self, bottom, top):
        shape = list(bottom[0].data.shape)
        top[0].reshape(*shape)
        top[1].reshape(*shape)

    def forward(self, bottom, top):
        channel = top[0].data.shape[0]
        for i in range(channel):
            top[0].data[i] = self.alpha*bottom[0].data + self.beta

        top[0].data[...] = quantize_inverse(top[0].data, self.bws[2], self.fls[2]).reshape(top[0].data.shape)

        top[1].data[...] = np.ones(top[1].data.shape)*self.alpha
        top[1].data[...] = quantize_inverse(top[1].data, self.bws[2], self.fls[2]).reshape(top[1].data.shape)


class ConstLayer(caffe.Layer):
    def setup(self, bottom, top):
        params = yaml.load(self.param_str)
        self.shape = params['shape']
        self.const = params['const']

    def reshape(self, bottom, top):
        top[0].reshape(*self.shape)

    def forward(self, bottom, top):
        top[0].data[...] = np.ones(self.shape)*self.const
        top[0].data[...] = quantize_inverse(top[0].data, self.bws[2], self.fls[2]).reshape(top[0].data.shape)
