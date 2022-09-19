use std::collections::VecDeque;

mod vm_parsers;
use vm_parsers::test;


struct VMParser {
  // ifs: std::ifstream,
  curr_command: String,
  curr_command_words: Vec<String>,
  commands: VecDeque<String>,
}

impl VMParser {
  fn new(infile: &str) -> VMParser {
    println!("Load {}", infile);

    let mut commands = VecDeque::new();
    let hoge: String = "hoge".to_string();
    commands.push_back(hoge);
    return VMParser{
      curr_command: String::new(),
      curr_command_words: Vec::new(),
      commands: commands,
    };
  }

  fn has_more_commands(&self) -> bool {
    return !(self.commands.is_empty());
  }

  fn advance(&mut self) {
    self.curr_command = self.commands.pop_front().unwrap();
    self.split_command();
    return;
  }

  fn split_command(&mut self) {
    self.curr_command_words = Vec::new();
    let curr_command_temp = &(self.curr_command);
    // loop {
    //   if 
    // }
    self.curr_command_words.push(curr_command_temp);
  }
}

fn main() {
  println!("Hello, world!");
  test();

  let input: &str = "hoge";

  let mut vm_parsers = VMParser::new(input);
  let _ = vm_parsers.has_more_commands();
  vm_parsers.advance();
}
