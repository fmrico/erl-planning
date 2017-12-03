
rosservice call /kcl_rosplan/update_knowledge_base "update_type: 0
knowledge:
  knowledge_type: 0
  instance_type: 'ball'
  instance_name: 'red'
  attribute_name: ''
  function_value: 0.0";

rosservice call /kcl_rosplan/update_knowledge_base "update_type: 0
knowledge:
  knowledge_type: 0
  instance_type: 'ball'
  instance_name: 'blue'
  attribute_name: ''
  function_value: 0.0";

rosservice call /kcl_rosplan/update_knowledge_base "update_type: 0
knowledge:
  knowledge_type: 0
  instance_type: 'box'
  instance_name: 'A'
  attribute_name: ''
  function_value: 0.0";

rosservice call /kcl_rosplan/update_knowledge_base "update_type: 0
knowledge:
  knowledge_type: 0
  instance_type: 'box'
  instance_name: 'B'
  attribute_name: ''
  function_value: 0.0";

rosservice call /kcl_rosplan/update_knowledge_base "update_type: 0
knowledge:
  knowledge_type: 0
  instance_type: 'box'
  instance_name: 'C'
  attribute_name: ''
  function_value: 0.0";

rosservice call /kcl_rosplan/update_knowledge_base "update_type: 0
knowledge:
  knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'ball_at_box'
  values:
    - {key: 'bl', value: 'red'}
    - {key: 'bx', value: 'A'}
  function_value: 0.0";

rosservice call /kcl_rosplan/update_knowledge_base "update_type: 0
knowledge:
  knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'ball_at_box'
  values:
    - {key: 'bl', value: 'blue'}
    - {key: 'bx', value: 'B'}
  function_value: 0.0";

rosservice call /kcl_rosplan/update_knowledge_base "update_type: 0
knowledge:
  knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'free'
  values:
    - {key: 'bx', value: 'C'}
  function_value: 0.0";

rosservice call /kcl_rosplan/update_knowledge_base "update_type: 1
knowledge:
  knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'ball_at_box'
  values:
    - {key: 'bl', value: 'red'}
    - {key: 'bx', value: 'B'}
  function_value: 0.0"

rosservice call /kcl_rosplan/planning_server;
