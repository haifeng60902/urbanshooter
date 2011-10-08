#ifndef _NODE_COLLECTOR_H_
#define _NODE_COLLECTOR_H_


#include <osg/NodeVisitor>
#include <vector>

/**
 *	NodeCollector is a way to get all nodes of the required type in a graph
 *	example : 
 *	std::vector<osg::Geode*> geodes = NodeCollector::collect<osg::Geode>(root_node);
*/
class NodeCollector
{
public:

	/** Launch the graph traversal and return the collected nodes */
	template <class T> static std::vector<T*> collect(osg::Node *node)
	{
		std::vector<T*> v;

		//collect nodes
		myCollector<T> mc;
		node->accept( mc );
		v = mc.getNodes();

		return v;
	}

	NodeCollector(){}
	~NodeCollector(){}

private :

	/** Node Visitor to collect the required nodes */
	template < class T >
	class myCollector : public osg::NodeVisitor
	{

		public :

			/** Default constructor : traverse all children */
			myCollector() : 
			   osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
			{
			}

			/** Destructor */
			~myCollector(){}

			
			/** virtual apply method implementation */
			void apply(osg::Node & node)
			{


				T* t = dynamic_cast<T*> (&node);

				if(t)
					_nodes.push_back(t);

				traverse(node);
			}

			/** Return the vector of nodes */
			std::vector<T*> getNodes(){ return _nodes; }

		private:

			std::vector<T*> _nodes;
	};


};


#endif //_NODE_COLLECTOR_H_
