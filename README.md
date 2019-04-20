# jsx
遗产链智能合约项目：

一、项目背景说明：
   
   在财产继承方面，遗嘱在分配遗产中具有最强的法律效益。常见的遗嘱形式包括公证遗嘱、自书遗嘱、代书遗嘱、录音遗嘱、口头遗嘱等。但是这些遗嘱形式并不能保证唯一性，而且这些都是很有可能产生争议的。常常发生巨额财产的遗产继承发生争议，部分继承人对遗嘱真实性产生质疑，或者同时出现多份公证遗嘱的复杂法律情况。例如齐白石弟子的21亿天价遗产纠纷案，香港巨富龚如心的天价遗产争夺案。所以如果存在一种方式，让遗嘱的形式唯一并且真实可信，那么可以大量减少此类的遗产争夺的法律争议。而区块链的出现恰好能很好的解决这个问题。

二、项目目前实现： 
    1、去中心化的设计，可以有效防止了只有部分中心化节点恶意去破坏遗嘱的真实性。例如曾经发生了部分律师恶意私藏，破坏遗嘱人的遗嘱的信息，导致遗嘱人的意愿不能实现。区块链的广播需要在一个小范围的联盟链上，并得到足够多，且身份信息合规并能够符合法律效力认证的人的确认，才承认该份遗嘱的有效性。
    2、遗嘱的唯一性。对于一份存储在链表中的遗嘱，只承认一份遗嘱的有效性，避免了多份遗嘱带来的法律争议。
    3、提供标准的遗嘱类型文档，可以让部分对法律了解不深的老人可以直接选择填表式选择制定遗嘱类型。
    
三、项目进一步构想：   
    1、隐私保护的有效性。对于遗嘱的存放，对于遗嘱人对于遗产的主体的信息保存在一条私有链上，只开放接口给部分公证人公证确保法律效力。
    2、遗嘱的的法律效力保障。在公证人的实现中，实现对公证人的身份认证，例如连接国家律师证明系统，对于公证人的身份信息有清晰明确的认证，增加了该份遗嘱的法律效力。
    3、遗嘱的真实性保障。时间戳的效力，并将取证时间发送至国家授时中心认证，以证明电子证据的生成时间，这样可以精准保证遗嘱确立的时间。该系统会自动对登记设备和网络环境进行检测，以确保真实；
    4、更复杂的遗嘱形式，对于多种实际情况下的遗嘱填写提供指导性的模板，并在后端的数据库上建立更加复杂的数据库模型。
    最终项目的目的是利用区块链技术的一站式老人遗嘱订立法律平台，从法律咨询、遗嘱订立、遗嘱保管、数据库管理以及遗嘱执行、争议调解进行全方位一体化服务，保证了遗嘱的安全必要性。
四、项目实现框架：
   主要实现框架，目前只搭建了底层基础的数据库类型的实现以及几类用户所需要的基本的操作以及简单的用户界面。
   前端设计：
   登录界面后用户可以有三种身份登录，遗嘱人，受益人，公证人。
   1、遗嘱人
   遗嘱人是这个系统的核心操作用户，该类用户具有最多的操作。主要的内容在于创建遗嘱信息并将这些信息全面记录到后端数据库中去。当他创建一个遗嘱的时候可以看到这个遗嘱的状态，如果未得到公证人认证的遗嘱不具备法律效应，只处于起草的状态。
   （1）、完善个人信息资料
   （2）、建立自己的遗嘱信息。
   （3）、确认自己的死亡，遗嘱
   2、受益人
   受益人的权限最低，相当于游客的浏览权限，只能查看是否有人将遗产馈赠给自己的权限。
   （1）、查看自己的接收遗产的信息
   3、公证人
   公证人权限较高，他的主要权限是确认遗嘱的合法性。当得到两名及以上的律师或者与财产分割没有利益相关人的认证后，这份遗嘱确认了法律效力。
   （1）、查看遗嘱的全部信息
   （2）、确认遗嘱的信息无误并且承认法律效力















