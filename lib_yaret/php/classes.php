<?php
require_once('DB.php');

DEFINE("TABLE_TYPE_MAIN",1);
DEFINE("TABLE_TYPE_ID",2);
DEFINE("TABLE_TYPE_MULTI_ID",3);
DEFINE("TABLE_TYPE_BACK_ID",4);

DEFINE("FIELD_TYPE_DIRECT",5); 	// adds normal queryable field
DEFINE("FIELD_TYPE_PER_ENTRY",6); 	// field which is saved in the connection table and so can be different for each conjunction (e.g track_nr in album)


class yaret_item_field_entry
{
	var $key;
	var $value;
}

class yaret_item
{
	var $field_list;
	var $type;
	var $db;
	
	function yaret_item($db)
	{
		$this->db=$db;
		
		$this->field_list = new yaret_list();
	}
	
	function generate_from_row($row)
	{
		if (is_array($row))
		{
			foreach ($row as $key => $value)
			{
				if (is_string($key))
				{
					$entry = new yaret_item_field_entry();
					$entry->key = $key;
					$entry->value = $value;
					$this->field_list->add($entry);
					
				}
			}
		}
	}
	
	function generate_from_id($id)
	{
		$sql = "select * from {$this->type} where id = $id";
		
		//echo $sql;
		if (!$result = $this->db->query($sql))
		{
			error_report(SQL_ERROR, 'generate' , __LINE__, __FILE__,$sql);
		}
		
		$row = $result->fetchRow(DB_FETCHMODE_ASSOC);
		return $this->generate_from_row($row);
	}
}


class yaret_vfs
{
	var $table_list;	
	var $query_list;
	var $maint_table;
	var $db;
	
	function yaret_vfs()
	{
		$this->table_list = new yaret_list();
		$this->query_list = new yaret_list();
		
		// connect to db
		$user = 'root';
		$pass = 'bla';
		$host = 'localhost';
		$db_name = 'yaret';

		$dsn = "mysql://$user:$pass@$host/$db_name";

		$this->db = DB::connect($dsn, true);

 		if (DB::isError($this->db))
 		{
			die ($this->db->getMessage());
 		}
	}
	
	
	
	function set_table_config($xml)
	{
		
		// main table;
		$table = new yaret_table();
		$table->set_type(TABLE_TYPE_MAIN);
		$table->set_name('titel');
		
		$field = new yaret_field();
		$field->set_field_type(FIELD_TYPE_DIRECT);
		$field->set_name('value');
		$field->set_table($table);
		$table->add_field($field);
		
		$this->table_list->add($table);
		$this->main_table = $table;
		
		// album table;
		$table = new yaret_table();
		$table->set_type(TABLE_TYPE_MULTI_ID);
		$table->set_name('album');
		
		$field = new yaret_field();
		$field->set_field_type(FIELD_TYPE_DIRECT);
		$field->set_name('value');
		$field->set_table($table);
		$table->add_field($field);
		
		$field = new yaret_field();
		$field->set_field_type(FIELD_TYPE_PER_ENTRY);
		$field->set_name('track_nr');
		$table->add_field($field);
	
		
		$this->table_list->add($table);
		
		// artist table;
		$table = new yaret_table();
		$table->set_type(TABLE_TYPE_MULTI_ID);
		$table->set_name('artist');
		
		$field = new yaret_field();
		$field->set_field_type(FIELD_TYPE_DIRECT);
		$field->set_name('value');
		$field->set_table($table);
		$table->add_field($field);
		
		
		$this->table_list->add($table);
		
		// genere table;
		$table = new yaret_table();
		$table->set_type(TABLE_TYPE_MULTI_ID);
		$table->set_name('genre');
		
		$field = new yaret_field();
		$field->set_field_type(FIELD_TYPE_DIRECT);
		$field->set_name('value');
		$field->set_table($table);
		$table->add_field($field);
		
		$this->table_list->add($table);
		
		
	}
	
	function set_query_config($xml)
	{
		$this->query_list->add($this->create_query_item("genre","value"));
		$this->query_list->add($this->create_query_item("artist","value"));
		$this->query_list->add($this->create_query_item("album","value"));
		$this->query_list->add($this->create_query_item("titel","value"));
	}
	
	function parse_path($url)
	{
		$path_list = new yaret_list();
				
		foreach (explode('/',$url) as $value)
		{
			if ($value != "")
			{
				$path_list->add($value);
				$param_anz++;
			}
		}
				
		
		return $path_list;
	}

	function sql_to_object_list($type,$result)
	{
		$item_list = new yaret_list();
		
		
		while ($row = $result->fetchRow()) 
		{
			// is eigentlich type aber field gibt das gleiche ich bin zu faul das orderntlich zu machen
			$item = new yaret_item($this->db);
			
			
			if ($row[0]!=NULL)
			{
				// item is a dir
				$item->type = $type;
				$item->generate_from_id($row[0]);
			}
			else
			{
				// item is a file
				$item->type = $this->main_table->name;
				$item->generate_from_id($row[1]);
			}
			$item_list->add($item);
				
		}
		
		return $item_list;
	}
	
	function make_dir($path)
	{
	
		$path_list = $this->parse_path($path);	
		
		$path_iterator = $path_list->get_iterator();
		$query_iterator = $this->query_list->get_iterator();
		
		$path_iterator->first();
		$query_iterator->first();
		
		$value_sql = " (value) VALUES ('".$path_iterator->CurrentItem()->item ."')";
		
		$path_iterator->next();
		
		while((!$path_iterator->IsDone()) and (!$query_iterator->IsDone()))
		{
			$path_iterator->next();
			$query_iterator->next();
		}
		
		
		$insert_sql = "INSERT INTO ". $query_iterator->CurrentItem()->item->get_table()->get_name();
		
		
		$sql=$insert_sql.$value_sql;
		
		echo $sql;
		
		$result = $this->db->query($sql);
		
		if (DB::isError($result)) 
		{
			die ($result->getMessage());
		}
		
		

		
	}
	
	function get_dirs($path)
	{
		// returns a list of dir objects
		
		$path_list = $this->parse_path($path);	
		
		$path_iterator = $path_list->get_iterator();
		$query_iterator = $this->query_list->get_iterator();
		
		
		
		$path_iterator->first();
		$query_iterator->first();
		
		
		
		while((!$path_iterator->IsDone()) and (!$query_iterator->IsDone()))
		{
			$from_sql .= $query_iterator->CurrentItem()->item->get_table()->get_from_sql($this->main_table);
		  $where_sql = " and ".$query_iterator->CurrentItem()->item->get_where_sql($path_iterator->CurrentItem()->item);
			$path_iterator->next();
			$query_iterator->next();
		}
		
		if ($query_iterator->IsDone())
		{
			if ($path_iterator->IsDone())
			{
				// path points to a file
				$query_iterator->last();
				$path_iterator->last();
				
			}
			else
			{
				// path was too deep return no such file or directory
				return NULL;
			}
		}
		else
		
		$from_sql .= $query_iterator->CurrentItem()->item->get_table()->get_from_sql($this->main_table);
		$from_sql = "FROM {$query_iterator->CurrentItem()->item->get_table()->get_name()} ";
		
		$select_sql = "SELECT ".$query_iterator->CurrentItem()->item->get_table()->get_name().".id as result, {$this->main_table->name}.id ";
		$sql = $select_sql . $from_sql. " WHERE 1 " .$where_sql." GROUP BY result";
		echo $sql;
		// execute query
		$result = $this->db->query($sql);

		// Always check that $result is not an error
		if (DB::isError($result)) 
		{
			die ($result->getMessage());
		}	
		
		return $this->sql_to_object_list($query_iterator->CurrentItem()->item->get_table()->get_name(),$result);
		
	
	}
	
	
	
	
	
	//private
	function create_query_item($table_name,$field_name)
	{
		$table = $this->get_table_by_name($table_name);
		
		$field = $table->get_field_by_name($field_name);
		return $field;
		
	}
	
	function get_table_by_name($table_name)
	{
		// find table object named $table
		
		$iterator = $this->table_list->get_iterator();
		$iterator->first();
		while (!$iterator->IsDone())
		{
			$table = $iterator->CurrentItem();
			if ($table->item->get_name() == $table_name)
			{
				return $table->item;
			}
			$iterator->next();
		}
		return NULL;
	}
}


class yaret_table
{
	var $type; // information how table is connected to main table (main,id, multi id, back id)
	var $field_list;
	var $name;
	
	function get_from_sql($main_table)
	{

		if ($this->type == TABLE_TYPE_MAIN)
		{	
			return $name;
		}
		elseif($this->type == TABLE_TYPE_MULTI_ID)
		{
			
			return "LEFT JOIN {$main_table->get_name()}_$this->name ON ({$main_table->get_name()}.id = {$main_table->get_name()}_$this->name.{$main_table->get_name()}_id) ". 
						 "LEFT JOIN $this->name ON ({$main_table->get_name()}_$this->name.{$this->name}_id = $this->name.id)";
		}
	}
	
	function get_field_by_name($field_name)
	{
		// find field object named $table
		$iterator = $this->field_list->get_iterator();
		$iterator->first();
		
		while (!$iterator->IsDone())
		{
			$field = $iterator->CurrentItem();
			if ($field->item->get_name() == $field_name)
			{
				return $field->item;
			}
			$iterator->next();
		}
		return NULL;
	}
	
	function yaret_table()
	{	
		$this->field_list = new yaret_list();
	}
	
	function set_type($type)
	{
		$this->type=$type;
	}
	
	function get_std_sql()
	{
		// returns the part after FROM (mainly LEFT JOINS)
	}
	
	function get_provided_fileds()
	{
		// fields provided by this table which can be put in query config
	}
	
	function add_field($field)
	{
		$field->table=$this;
		$this->field_list->add($field);
		
	}
	
	function set_name($name)
	{
		$this->name=$name;
	}
	
	function get_name()
	{
		return $this->name;
	}

}

class yaret_field
{
	var $type;
	var $table; //holds pointer to the table
	var $name;
	var $value; // for querys: value  that this field should be
	
	function get_where_sql($value)
	{
		return "{$this->table->get_name()}.$this->name = '$value'";
	}
	
	function set_field_type($type)
	{
		$this->type=$type;
	}
	
	function set_name($name)
	{
		$this->name=$name;
	}
	
	function get_name()
	{
		return $this->name;
	}
	
	function set_table($table)
	{
		$this->table=$table;
	}
	
	function get_table()
	{
		return $this->table;
	}
	
	
	
	
}

class yaret_list
{	
	var $first;
	var $last;
	
	function get_iterator()
	{
		$iterator = new yaret_list_iterator($this);
		return $iterator;
	}
	function add($yaret_table)
	{
		
		$item=new yaret_list_item();
		$item->item=$yaret_table;
		
		//echo $this->first;
		
		if (!is_object($this->first))
		{
			
			$this->first=$item;
			$this->last=$item;
			
			
		}
		else
		{
			$this->last->next=$item;
			$item->prev=$this->last;
			$this->last=$item;
		}
	}
	
}

class yaret_list_item
{
	var $next;
	var $prev;
	var $item;
}


class yaret_list_iterator
{
	var $current_item;
	var $list;
	
	function yaret_list_iterator($list)
	{
		$this->list=$list;
	}
	
	function first()
	{
		$this->current_item = $this->list->first;
	}
	
	function last()
	{
		$this->current_item = $this->list->last;
	}
	
	function next()
	{
		$this->current_item = $this->current_item->next;
	}
	
	
	
	function CurrentItem()
	{
		return $this->current_item;
	}
	
	function IsDone()
	{
		
		
		if (isset($this->current_item))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}


// test code
$yaret = new yaret_vfs;
$yaret->set_table_config("nix");
$yaret->set_query_config("nix");
if ($argv[1] == 'md')
{
	echo $yaret->make_dir($argv[2]);
}
else
{
$dirs =  $yaret->get_dirs($argv[2]);

if ($dirs==NULL)
{
	die("NO");
}
$iterator = $dirs->get_iterator();
$iterator->first();
while(!$iterator->IsDone())
{
	$fi = ($iterator->CurrentItem()->item->field_list->get_iterator());
	
	$fi->first();
	while(!$fi->IsDone())
	{
		
	 echo $iterator->CurrentItem()->item->type.":  ".($fi->CurrentItem()->item->key)." = ".($fi->CurrentItem()->item->value)."\n";
		$fi->next();
	}

	
	
	$iterator->next();
	
}
}
?>
