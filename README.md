# [environ](https://github.com/Qful/environ)

[![sites](Qful/qitas.png)](http://www.Qful.net)

## [environ简介](https://github.com/Qful/environ)

环境管理组件，通过传感器收集相应的数据并根据管理策略和权限执行相应的控制，例如闭环的温度管理噪音管理等，对于可消除的因素进行消除，不可消除的进行补偿，尽量减少不利的影响，而且可以从云端获取相应的支持，消除不利的环境因素。

环境管理组件作为一个子系统，需要更加智能或者是可以智能化升级，不单单是是一个数据采集端，而这个指挥的组件可以被更多上层的智能硬件集成。

本工程主要针对通用化的智能环境管理，最大化平衡设备的各种性能，提供最典型的集成化方案，也是客制化的一个模板工程，将定义出智能的形态和互补提升。

主要监控参数：

* 温湿
* 辐照
* 压力
* 声场

针对数据采集采用相应的传感器阵列，采用[Q1体系](https://github.com/OS-Q/Q1)边缘设备解决方案，集成大量的设备节点，针对环境的改变控制采用[Q4体系](https://github.com/OS-Q/Q4)体系实现相应的控制输出。

本工程对应的每个参数管控都需要有对应的处理和干涉机制，可消除可补偿，而这些额外的设备的控制都在本工程实现中。

### [工程目录](https://github.com/Qful/environ)

* [文档](docs/)
* [资源](src/)
* [工程](project/)

### [Q资源](https://github.com/Qful)

* [Q系统](https://github.com/OS-Q)
* [Q硬件](https://github.com/sochub)
* [Q智慧](https://github.com/tfzoo)
* [Q品质](https://github.com/qitas)

### www.Qful.net


