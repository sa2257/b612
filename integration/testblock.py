import os,sys,inspect
currentdir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
parentdir = os.path.dirname(currentdir)
sys.path.insert(0,parentdir) 
from itertools import chain
from collections import deque
from Q import processingElement, unitQ

fileName = "simplevvadd.map"
#fileName = "../prepping/simplegemm.map"

peMapping = {}
peLayout = {}
nodeMapping = {}
nodeLayout = {}

def configure():
    global peLayout
    global nodeLayout
    global peMapping
    global nodeMapping
    d = 0
    item = 1
    f = open(fileName, "r")
    for x in f:
        if ('%%' not in x):
            my_string = x.strip('\n')
            my_list = my_string.split(",")
            my_list = ' '.join(my_list).split() 
            if (d is 0):
                peLayout[item] = [int(i) if ('None' not in i) else None for i in my_list]
            elif (d is 1):
                nodeLayout[item] = [int(i) if ('None' not in i) else None for i in my_list]
            elif (d is 2):
                int_list = [int(i) if ('None' not in i) else None for i in [my_list[1], my_list[2]]]
                bool_list = True if ('True' in my_list[3]) else False
                peMapping[item] = {'func': my_list[0], 'in': int_list, 'out': bool_list}
            else:
                in_list = [int(i) if ('None' not in i) else None for i in [my_list[0], my_list[1], my_list[2]]]
                bool_list = True if ('True' in my_list[3]) else False
                nodeMapping[item] = {'ein': in_list[0], 'eout': in_list[1], 'in': in_list[2], 'out': bool_list}
            item =  item + 1
        else:
            item = 1
            d = d + 1
    
def initialize():
    nodes = []
    for q in list(nodeMapping):
        nodes.append([None, None, None, None, None, None, None, None])
    return nodes

def q2pe_mapping(nodes):
    compute = []
    for i, pe in enumerate(list(peMapping)):
        compute.append([None, None])
        for j, each in enumerate(peMapping[pe]['in']):
            if each is not None:
                compute[i][j] = nodes[peLayout[pe][each] - 1]
    return compute

def pe2q_mapping(compute, nodes):
    new_nodes = []
    for i, q in enumerate(list(nodeMapping)):
        new_nodes.append([None, None, None, None, None, None, None, None])
        each = nodeMapping[q]['in']
        if each is not None:
            if each > 3:
                new_nodes[i][each] = compute[nodeLayout[q][each] - 1]
            else:
                new_nodes[i][each] = nodes[nodeLayout[q][each] - 1]
    return new_nodes

def simulate(input_queues, output_queues, ready_queue, check_queue, max_ticks, size): 
    input_queues = input_queues[0]
    output_queues = output_queues[0]
    ready_queue = ready_queue[0]
    check_queue = ready_queue[0]
    # input arguments come as tuples, even though a 6 item tuple was sent from C
    # make the stupid tuples, lists
    configure()
    ticks = 0

    # Define nodes
    Q_LIST = []
    for idx in nodeMapping:
        node =  nodeMapping[idx]
        outT = False
        if node['eout'] is not None:
            outT = True
        if node['ein'] is not None:
            QU = unitQ('QU' + str(idx), True, node['ein'], False, None, outT, node['eout'], 8)
        else:
            each = node['in']
            if each is None:
                QU = unitQ('QU' + str(idx), False, None, False, each, outT, node['eout'], 8)
            elif each > 3:
                QU = unitQ('QU' + str(idx), False, None, False, each, outT, node['eout'], 8)
            else:
                QU = unitQ('QU' + str(idx), False, None, True , each, outT, node['eout'], 8)
        Q_LIST.append(QU)
    
    # Define operators
    PE_LIST = []
    for idx in peMapping:
        pe = peMapping[idx]
        PE = processingElement('PE' + str(idx), pe['func'], False, 1, 4, 1, False, False, False)
        PE_LIST.append(PE)
    
    # Initialize
    inNode = initialize()
    
    # Execute
    while ticks < max_ticks:
        outNode = []
        outTicks = []
        for i, Q in enumerate(Q_LIST):
            node, output_queues, ready_queue, tempTicks = Q.route(inNode[i], input_queues, output_queues, ready_queue, ticks)
            outNode.append(node)
            outTicks.append(tempTicks)
        ticks = max(outTicks)
        
        inWire = q2pe_mapping(outNode)
        
        outWire = []
        outTicks = []
        for i, PE in enumerate(PE_LIST):
            compute, tempTicks = PE.operate(inWire[i], ticks)
            outWire.append(compute)
            outTicks.append(tempTicks)
        #print('pe output queue {}'.format(outWire))
        ticks = max(outTicks)
        
        inNode = pe2q_mapping(outWire, outNode)
    
    # Check result
    return output_queues

if __name__ == "__main__":
    # execute only if run as a script
    #output_queues = simulate([5.0, 6.0, 30.0], [0.0, 0.0, 0.0], [True, True, True], [True, True, True], 5, 3) # gemm
    output_queues = simulate([5.0, 6.0], [0.0, 0.0], [True, True], [True, True], 3, 2) # vvadd
    print('Output array when time ran out: {}'.format(output_queues))
