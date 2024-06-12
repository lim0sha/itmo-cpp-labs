#include "RubicsCube.h"

using namespace std;

static CubeInits CI;

void swapArrayElements(int8_t *A, const int *C) {
  int8_t curr = A[C[3]];
  A[C[3]] = A[C[2]];
  A[C[2]] = A[C[1]];
  A[C[1]] = A[C[0]];
  A[C[0]] = curr;
}

void RubicsCube::do_rotate(Plate::Side side_type, int value_count) {
  // поворотов от 0 до 3
  value_count = (value_count >= 0) ? value_count % 4 : (value_count % 4) + 4;
  // value_count >> 1 делит value_count на 2, чтобы получить индекс в массиве (т.к. каждый второй элемент отвечает за следующую итерацию поворотов)
  std::vector<int> &sttc_Corners = CI.Map_CROT[value_count >> 1].at(int(side_type));
  std::vector<int> &sttc_Edges = CI.Map_EROT[value_count >> 1].at(int(side_type));
  // поворот на 180, просто меняем местами пары
  if (value_count == 2) {
    swap(corners_padding_[sttc_Corners[0]], corners_padding_[sttc_Corners[2]]);
    swap(corners_padding_[sttc_Corners[1]], corners_padding_[sttc_Corners[3]]);
    swap(corners_init_[sttc_Corners[0]], corners_init_[sttc_Corners[2]]);
    swap(corners_init_[sttc_Corners[1]], corners_init_[sttc_Corners[3]]);
  } else {
    // поворот на 90 или 270
    swapArrayElements(corners_padding_, sttc_Corners.data());
    swapArrayElements(corners_init_, sttc_Corners.data());
    if (int(side_type) >= 2) {
      for (int i = 0; i < 4; ++i) {
        corners_init_[sttc_Corners[i]] = static_cast<int8_t>((corners_init_[sttc_Corners[i]] + (i % 2 == 0 ? 1 : -1) + 3) % 3);
      }
    }
    if (int(side_type) >= 4) {
      for (int i = 0; i < 4; ++i) {
        edges_init_[sttc_Edges[i]] ^= 1;
      }
    }
    swapArrayElements(edges_padding_, sttc_Edges.data());
    swapArrayElements(edges_init_, sttc_Edges.data());
  }
}

Margin RubicsCube::get_margin(int position, int x_axis, int y_axis) const {
  // функция для получения состояния граней
  auto ind = static_cast<int8_t>(position * 9 + x_axis * 3 + y_axis);
  int8_t F_margin[6] = {-1, -1, -1, -1, -1, -1};
  // углы
  if (position != 1 and x_axis != 1 and y_axis != 1) {
    int8_t id = (position << 1) | x_axis | ((x_axis ^ y_axis) >> 1);
    int8_t *Orient = CI.Map_CORI[id];
    int8_t *CornOrient = CI.Map_CORI[corners_padding_[id]];
    F_margin[Orient[0]] = CornOrient[corners_init_[id]];
    F_margin[Orient[1]] = CornOrient[(1 + corners_init_[id]) % 3];
    F_margin[Orient[2]] = CornOrient[(2 + corners_init_[id]) % 3];
    // ребра
  } else if (CI.Map_EINDEX[ind] != -1) {
    int8_t id = CI.Map_EINDEX[ind];
    int8_t *O = CI.Map_EORI[id];
    int8_t *C = CI.Map_EORI[edges_padding_[id]];
    F_margin[O[0]] = C[edges_init_[id]];
    F_margin[O[1]] = C[edges_init_[id] ^ 1];
    // центры
  } else if (position != 1 or x_axis != 1 or y_axis != 1) {
    F_margin[CI.Map_CNTRINDEX[ind]] = CI.Map_CNTRINDEX[ind];
  }
  return {F_margin[0], F_margin[1], F_margin[2], F_margin[3], F_margin[4], F_margin[5]};
}

void VirtualOrb::init_rotation_vector(long double angle, Vector v_pos) {
  // вектор обзора
  erase_initialization();
  glPushMatrix();
  glRotated(angle, v_pos.x_axis, v_pos.y_axis, v_pos.z_axis);
  glGetFloatv(GL_MODELVIEW_MATRIX, buffer_);
  glPopMatrix();
}

VirtualOrb::VirtualOrb() {
  radius_ = 0.5;
  erase_initialization();
}

void VirtualOrb::do_rotate() {
  glMultMatrixf(buffer_);
  glRotated(angle_, init_axis_.x_axis, init_axis_.y_axis, init_axis_.z_axis);
}

void VirtualOrb::erase_initialization() {
  init_axis_.x_axis = 1;
  angle_ = init_axis_.y_axis = init_axis_.z_axis = 0;
}

bool GlMonitor::init() {
  if (!glfwInit())
    return false;
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHint(GLFW_SAMPLES, 4);
  gl_window_ = glfwCreateWindow(600, 600, "Cube", nullptr, nullptr);
  glfwSetWindowUserPointer(gl_window_, this);
  glfwSetKeyCallback(gl_window_, keyboard_response);
  glfwSetInputMode(gl_window_, GLFW_STICKY_KEYS, 1);
  glfwMakeContextCurrent(gl_window_);
  glEnable(GL_DEPTH_TEST);
  virtual_orb_.init_rotation_vector(35, {-1, -1, 0});
  return true;
}

void GlMonitor::run() {
  while (!glfwWindowShouldClose(gl_window_)) {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    process_rotations();
    display(cube_template_);
    glfwSwapBuffers(gl_window_);
  }
  glfwTerminate();
}

GlMonitor::GlMonitor() {
  fill(rotation_type_buffer_, rotation_type_buffer_ + 3, -1);
}

void GlMonitor::init_cube(const RubicsCube &rubics_cube) {
  this->cube_template_ = rubics_cube;
}

void GlMonitor::queue_push_rotation(Plate::Side c_side, int d_param, int value) {
  queue_moves_.emplace(c_side, d_param, value % 4);
}

void GlMonitor::process_rotations() {
  if (queue_moves_.empty() or MvSqs_.isActive()) {
    return;
  }
  Plate::Side side_type;
  int d_param, counter;
  std::tie(side_type, d_param, counter) = queue_moves_.front();
  fill(rotation_type_buffer_, rotation_type_buffer_ + 3, -1);
  rotation_vector_ = counter < 0 ? -1 : 1;
  static const std::map<Plate::Side, std::vector<int>> maskMap = {
      {Plate::T, {3, -1, -1}}, {Plate::BT, {-1, 1, -1}}, {Plate::L, {-1, -1, 1}}, {Plate::R, {-1, -1, 3}},
      {Plate::F, {-1, 3, -1}}, {Plate::BC, {1, -1, -1}}
  };
  auto it = maskMap.find(side_type);
  if (it != maskMap.end()) {
    for (size_t i = 0; i < it->second.size(); ++i) {
      if (it->second[i] != -1) {
        rotation_type_buffer_[i] = it->second[i];
      }
    } if (counter < 0) {
      rotation_vector_ = -rotation_vector_;
    }
  }
  cube_template_.do_rotate(side_type, counter);
  queue_moves_.pop();
}

void GlMonitor::keyboard_response(GLFWwindow *glf_wwindow, int key_pushed, int _act, int action, int _mode) {
  auto *p_gl_monitor = reinterpret_cast<GlMonitor *>(glfwGetWindowUserPointer(glf_wwindow));
  static const std::map<int, std::tuple<Plate::Side, int, int>> keyMap = {
      {'1', {Plate::L, 1, 1}}, {'Q', {Plate::L, 1, -1}}, {'2', {Plate::R, 1, -1}}, {'W', {Plate::R, 1, 1}},
      {'3', {Plate::T, 1, 1}}, {'E', {Plate::T, 1, -1}}, {'4', {Plate::BT, 1, 1}}, {'R', {Plate::BT, 1, -1}},
      {'5', {Plate::F, 1, 1}}, {'T', {Plate::F, 1, -1}}, {'6', {Plate::BC, 1, 1}}, {'Y', {Plate::BC, 1, -1}}
  };

  if (action == GLFW_PRESS) {
    if (key_pushed == GLFW_KEY_U) {
      p_gl_monitor->cube_template_.save_state("cube_state.txt");
    } else if (key_pushed == GLFW_KEY_I) {
      p_gl_monitor->cube_template_.load_state("cube_state.txt");
    } else if (key_pushed == GLFW_KEY_O) {
      p_gl_monitor->cube_template_.print_state();
    } else if (key_pushed == GLFW_KEY_P) {
      p_gl_monitor->cube_template_.generate_random_state();
    } else if (key_pushed == GLFW_KEY_0) {
      if (p_gl_monitor->cube_template_.is_valid_state()) {
        std::cout << "The current state is valid." << std::endl;
      } else {
        std::cout << "The current state is not valid." << std::endl;
      }
    } else {
      auto it = keyMap.find(key_pushed);
      if (it != keyMap.end()) {
        const auto& [plate, depth, direction] = it->second;
        p_gl_monitor->queue_push_rotation(plate, depth, direction);
      }
    }
  }
}


void GlMonitor::draw_margin_side(GLfloat X_ax, GLfloat Y_ax, GLfloat Z_ax, GLfloat GL_value, Margin color, GLenum type) {
  GLfloat vertices[6][4][3] = { // массив вершин для каждой стороны блока
      {{X_ax, Y_ax, Z_ax}, {X_ax, Y_ax + GL_value, Z_ax}, {X_ax + GL_value, Y_ax + GL_value, Z_ax}, {X_ax + GL_value, Y_ax, Z_ax}}, // back
      {{X_ax, Y_ax, Z_ax - GL_value}, {X_ax, Y_ax + GL_value, Z_ax - GL_value}, {X_ax + GL_value, Y_ax + GL_value, Z_ax - GL_value}, {X_ax + GL_value, Y_ax, Z_ax - GL_value}}, // front
      {{X_ax, Y_ax + GL_value, Z_ax}, {X_ax + GL_value, Y_ax + GL_value, Z_ax}, {X_ax + GL_value, Y_ax + GL_value, Z_ax - GL_value}, {X_ax, Y_ax + GL_value, Z_ax - GL_value}}, // top
      {{X_ax, Y_ax, Z_ax}, {X_ax + GL_value, Y_ax, Z_ax}, {X_ax + GL_value, Y_ax, Z_ax - GL_value}, {X_ax, Y_ax, Z_ax - GL_value}}, // bottom
      {{X_ax, Y_ax, Z_ax}, {X_ax, Y_ax + GL_value, Z_ax}, {X_ax, Y_ax + GL_value, Z_ax - GL_value}, {X_ax, Y_ax, Z_ax - GL_value}}, // left
      {{X_ax + GL_value, Y_ax, Z_ax}, {X_ax + GL_value, Y_ax + GL_value, Z_ax}, {X_ax + GL_value, Y_ax + GL_value, Z_ax - GL_value}, {X_ax + GL_value, Y_ax, Z_ax - GL_value}} // right
  };
  int8_t colors_[6] = {color.back_, color.front_, color.top_, color.bottom_, color.left_, color.right_}; // массив цветов для каждой стороны блока
  for (int i = 0; i < 6; ++i) { // отрисовка каждой стороны блока
    init_color(colors_[i]);
    glBegin(type);
    for (int j = 0; j < 4; ++j) {
      glVertex3fv(vertices[i][j]);
    }
    glEnd();
  }
}

void GlMonitor::init_color(int color_code) {
  const GLfloat *Color_mas = CI.Gl_colors[color_code];
  glColor3f(Color_mas[0], Color_mas[1], Color_mas[2]);
}

void GlMonitor::display(const RubicsCube &rubics_cube) {
  GLfloat size = 0.8f / 3;
  glPushMatrix();
  virtual_orb_.do_rotate();
  // ширина линий отрисовки кубиков
  glLineWidth(2.f);
  // чтобы кубик был отцентрован
  GLfloat gl_base = -size * 3 * 0.5f, x_axis, y_axis, z_axis;
  static_cast<void>(x_axis = y_axis = gl_base), z_axis = -gl_base;
  for (int i = 0; i != 3; ++i, y_axis += size, x_axis = gl_base, z_axis = -gl_base) {
    for (int j = 0; j != 3; ++j, z_axis -= size, x_axis = gl_base) {
      for (int k = 0; k != 3; ++k, x_axis += size) {
        // рисует грани
        draw_margin_side(x_axis, y_axis, z_axis, size, rubics_cube.get_margin(i, j, k), GL_QUADS);
        // рисует границы блоков
        draw_margin_side(x_axis, y_axis, z_axis, size, {6, 6, 6, 6, 6, 6}, GL_LINE_LOOP);
      }
    }
  }
  // обновить состояние
  glPopMatrix();
}

GlMonitor* createOpenglViewer() {
  return new GlMonitor();
}

void RubicsCube::save_state(const std::string &filename) const {
  std::ofstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file for saving state");
  }
  for (const auto &val : corners_padding_) {
    file << static_cast<int>(val) << " ";
  }
  file << std::endl;
  for (const auto &val : edges_padding_) {
    file << static_cast<int>(val) << " ";
  }
  file << std::endl;
  for (const auto &val : corners_init_) {
    file << static_cast<int>(val) << " ";
  }
  file << std::endl;
  for (const auto &val : edges_init_) {
    file << static_cast<int>(val) << " ";
  }
  file << std::endl;
  file.close();
}

void RubicsCube::load_state(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file for loading state");
  }
  for (auto &val : corners_padding_) {
    int temp;
    file >> temp;
    val = static_cast<int8_t>(temp);
  }
  for (auto &val : edges_padding_) {
    int temp;
    file >> temp;
    val = static_cast<int8_t>(temp);
  }
  for (auto &val : corners_init_) {
    int temp;
    file >> temp;
    val = static_cast<int8_t>(temp);
  }
  for (auto &val : edges_init_) {
    int temp;
    file >> temp;
    val = static_cast<int8_t>(temp);
  }

  file.close();
}

void RubicsCube::print_state() const {
  std::cout << "Corners Padding: ";
  for (const auto &val : corners_padding_) {
    std::cout << static_cast<int>(val) << " ";
  }
  std::cout << std::endl;

  std::cout << "Edges Padding: ";
  for (const auto &val : edges_padding_) {
    std::cout << static_cast<int>(val) << " ";
  }
  std::cout << std::endl;

  std::cout << "Corners Init: ";
  for (const auto &val : corners_init_) {
    std::cout << static_cast<int>(val) << " ";
  }
  std::cout << std::endl;

  std::cout << "Edges Init: ";
  for (const auto &val : edges_init_) {
    std::cout << static_cast<int>(val) << " ";
  }
  std::cout << std::endl;
}

bool RubicsCube::is_valid_state() const {
  // corners
  std::array<int, 8> corner_count = {0};
  std::array<int, 12> edge_count = {0};
  for (signed char i : corners_padding_) {
    if (i < 0 || i >= 8) return false;
    corner_count[i]++;
  }
  for (int count : corner_count) {
    if (count != 1) return false;
  }
  // edges
  for (signed char i : edges_padding_) {
    if (i < 0 || i >= 12) return false;
    edge_count[i]++;
  }
  for (int count : edge_count) {
    if (count != 1) return false;
  }
  return true;
}

void RubicsCube::generate_random_state() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 2);
  for (auto &val : corners_init_) {
    val = dis(gen);
  }
  std::shuffle(std::begin(corners_padding_), std::end(corners_padding_), gen);
  for (auto &val : edges_init_) {
    val = dis(gen) % 2;
  }
  std::shuffle(std::begin(edges_padding_), std::end(edges_padding_), gen);
}
