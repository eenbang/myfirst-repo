// 游戏配置
const COLS = 15;
const ROWS = 20;
const BLOCK_SIZE = 30;

// 游戏状态
let board = [];
let currentPiece = null;
let nextPiece = null;
let score = 0;
let level = 1;
let lines = 0;
let gameRunning = false;
let gamePaused = false;
let dropTime = 0;
let lastTime = 0;
let trailHistory = []; // 荧光尾巴历史位置点
let lastPiecePosition = null; // 上次方块位置
let backgroundImage = null; // 背景图片
let gameDifficulty = 'medium'; // 游戏难度：'easy', 'medium', 'hard'
let gameStarted = false; // 游戏是否已开始

// 音频对象
let backgroundMusic = null; // 当前背景音乐
let backgroundMusicList = []; // 背景音乐列表
let currentMusicIndex = 0; // 当前音乐索引
let moveSound = null; // 移动音效
let rotateSound = null; // 旋转音效
let landSound = null; // 触底音效
let clearSound = null; // 消除行音效
let failSound = null; // 游戏结束音效
let musicMuted = false; // 音乐是否被静音

// 七种方块形状
const SHAPES = [
    // I
    [
        [0, 0, 0, 0],
        [1, 1, 1, 1],
        [0, 0, 0, 0],
        [0, 0, 0, 0]
    ],
    // O
    [
        [1, 1],
        [1, 1]
    ],
    // T
    [
        [0, 1, 0],
        [1, 1, 1],
        [0, 0, 0]
    ],
    // S
    [
        [0, 1, 1],
        [1, 1, 0],
        [0, 0, 0]
    ],
    // Z
    [
        [1, 1, 0],
        [0, 1, 1],
        [0, 0, 0]
    ],
    // J
    [
        [1, 0, 0],
        [1, 1, 1],
        [0, 0, 0]
    ],
    // L
    [
        [0, 0, 1],
        [1, 1, 1],
        [0, 0, 0]
    ]
];

// 方块颜色 - 二次元风格柔和色彩
const COLORS = [
    '#FFB6E1', // I - 粉色
    '#FFE5B4', // O - 淡黄色
    '#D4A5FF', // T - 淡紫色
    '#B5FFB5', // S - 淡绿色
    '#FFAAAA', // Z - 淡红色
    '#A5D5FF', // J - 淡蓝色
    '#FFD4A5'  // L - 淡橙色
];

// 初始化游戏板
function initBoard() {
    board = Array(ROWS).fill(null).map(() => Array(COLS).fill(0));
}

// 创建新方块
function createPiece() {
    const type = Math.floor(Math.random() * SHAPES.length);
    const shape = SHAPES[type].map(row => [...row]);
    return {
        shape: shape,
        x: Math.floor((COLS - shape[0].length) / 2),
        y: 0,
        color: COLORS[type]
    };
}

// 绘制单个方块 - 玻璃质感效果
function drawBlock(ctx, x, y, color, alpha = 0.6, isTrail = false) {
    const px = x * BLOCK_SIZE;
    const py = y * BLOCK_SIZE;
    const radius = 5; // 圆角半径
    
    // 保存上下文状态
    ctx.save();
    
    // 绘制圆角矩形路径
    ctx.beginPath();
    ctx.moveTo(px + radius, py);
    ctx.lineTo(px + BLOCK_SIZE - radius, py);
    ctx.quadraticCurveTo(px + BLOCK_SIZE, py, px + BLOCK_SIZE, py + radius);
    ctx.lineTo(px + BLOCK_SIZE, py + BLOCK_SIZE - radius);
    ctx.quadraticCurveTo(px + BLOCK_SIZE, py + BLOCK_SIZE, px + BLOCK_SIZE - radius, py + BLOCK_SIZE);
    ctx.lineTo(px + radius, py + BLOCK_SIZE);
    ctx.quadraticCurveTo(px, py + BLOCK_SIZE, px, py + BLOCK_SIZE - radius);
    ctx.lineTo(px, py + radius);
    ctx.quadraticCurveTo(px, py, px + radius, py);
    ctx.closePath();
    
    // 玻璃质感 - 使用透明度
    const baseColor = hexToRgb(color);
    ctx.fillStyle = `rgba(${baseColor.r}, ${baseColor.g}, ${baseColor.b}, ${alpha})`;
    ctx.fill();
    
    // 玻璃边框 - 白色半透明
    ctx.strokeStyle = `rgba(255, 255, 255, ${alpha * 0.8})`;
    ctx.lineWidth = 2;
    ctx.stroke();
    
    // 玻璃高光效果 - 渐变高光
    const highlightGradient = ctx.createLinearGradient(px, py, px + BLOCK_SIZE, py + BLOCK_SIZE * 0.6);
    highlightGradient.addColorStop(0, `rgba(255, 255, 255, ${alpha * 0.6})`);
    highlightGradient.addColorStop(0.5, `rgba(255, 255, 255, ${alpha * 0.2})`);
    highlightGradient.addColorStop(1, 'rgba(255, 255, 255, 0)');
    ctx.fillStyle = highlightGradient;
    ctx.fill();
    
    // 玻璃反射效果 - 底部反光
    const reflectionGradient = ctx.createLinearGradient(px, py + BLOCK_SIZE * 0.5, px + BLOCK_SIZE, py + BLOCK_SIZE);
    reflectionGradient.addColorStop(0, 'rgba(255, 255, 255, 0)');
    reflectionGradient.addColorStop(1, `rgba(255, 255, 255, ${alpha * 0.3})`);
    ctx.fillStyle = reflectionGradient;
    ctx.fill();
    
    // 玻璃装饰亮点
    if (!isTrail) {
        ctx.fillStyle = `rgba(255, 255, 255, ${alpha * 0.8})`;
        ctx.beginPath();
        ctx.arc(px + BLOCK_SIZE * 0.3, py + BLOCK_SIZE * 0.3, 2.5, 0, Math.PI * 2);
        ctx.fill();
    }
    
    ctx.restore();
}

// 将十六进制颜色转换为RGB
function hexToRgb(hex) {
    const result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
    return result ? {
        r: parseInt(result[1], 16),
        g: parseInt(result[2], 16),
        b: parseInt(result[3], 16)
    } : { r: 255, g: 182, b: 225 };
}

// 绘制荧光尾巴射线效果
function drawTrailEffect(ctx) {
    if (!currentPiece || trailHistory.length === 0) return;
    
    const color = hexToRgb(currentPiece.color);
    const centerX = currentPiece.x + currentPiece.shape[0].length / 2;
    const centerY = currentPiece.y + currentPiece.shape.length / 2;
    const centerPx = (centerX * BLOCK_SIZE) + (BLOCK_SIZE / 2);
    const centerPy = (centerY * BLOCK_SIZE) + (BLOCK_SIZE / 2);
    
    // 绘制从当前位置到历史位置的射线尾巴
    for (let i = 0; i < trailHistory.length; i++) {
        const history = trailHistory[i];
        const histCenterX = history.x + history.shape[0].length / 2;
        const histCenterY = history.y + history.shape.length / 2;
        const histPx = (histCenterX * BLOCK_SIZE) + (BLOCK_SIZE / 2);
        const histPy = (histCenterY * BLOCK_SIZE) + (BLOCK_SIZE / 2);
        
        // 计算距离和方向
        const dx = histPx - centerPx;
        const dy = histPy - centerPy;
        const distance = Math.sqrt(dx * dx + dy * dy);
        
        // 如果距离太近或太远，跳过
        if (distance < 5 || distance > BLOCK_SIZE * 10) continue;
        
        // 计算淡出透明度（越远的点越透明）
        const alpha = (1 - i / trailHistory.length) * 0.6;
        
        ctx.save();
        
        // 绘制发光的射线尾巴
        // 使用渐变从当前位置到历史位置
        const gradient = ctx.createLinearGradient(centerPx, centerPy, histPx, histPy);
        
        // 起点（当前位置）- 更亮
        gradient.addColorStop(0, `rgba(${color.r}, ${color.g}, ${color.b}, ${alpha * 0.8})`);
        // 中点
        gradient.addColorStop(0.5, `rgba(${color.r}, ${color.g}, ${color.b}, ${alpha * 0.5})`);
        // 终点（历史位置）- 更透明
        gradient.addColorStop(1, `rgba(${color.r}, ${color.g}, ${color.b}, ${alpha * 0.2})`);
        
        ctx.strokeStyle = gradient;
        
        // 绘制多个层次，营造发光效果
        for (let layer = 0; layer < 3; layer++) {
            const width = (3 - layer) * 2 + 1; // 外层更宽
            const layerAlpha = alpha * (1 - layer * 0.3);
            
            ctx.lineWidth = width;
            ctx.globalAlpha = layerAlpha;
            
            ctx.beginPath();
            ctx.moveTo(centerPx, centerPy);
            ctx.lineTo(histPx, histPy);
            ctx.stroke();
        }
        
        // 在历史位置绘制发光点
        const pointGradient = ctx.createRadialGradient(histPx, histPy, 0, histPx, histPy, BLOCK_SIZE);
        pointGradient.addColorStop(0, `rgba(${color.r}, ${color.g}, ${color.b}, ${alpha * 0.8})`);
        pointGradient.addColorStop(0.5, `rgba(${color.r}, ${color.g}, ${color.b}, ${alpha * 0.4})`);
        pointGradient.addColorStop(1, `rgba(${color.r}, ${color.g}, ${color.b}, 0)`);
        
        ctx.fillStyle = pointGradient;
        ctx.beginPath();
        ctx.arc(histPx, histPy, BLOCK_SIZE * 0.6, 0, Math.PI * 2);
        ctx.fill();
        
        ctx.restore();
    }
    
    // 清理过期历史点
    while (trailHistory.length > 6) {
        trailHistory.shift();
    }
}

// 绘制游戏板
function drawBoard(ctx) {
    // 清空画布
    ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height);
    
    // 绘制背景图片
    if (backgroundImage) {
        // 计算背景图片的缩放，使其适配画布并保持宽高比
        const imgAspect = backgroundImage.width / backgroundImage.height;
        const canvasAspect = ctx.canvas.width / ctx.canvas.height;
        
        let drawWidth, drawHeight, drawX, drawY;
        
        if (imgAspect > canvasAspect) {
            // 图片更宽，按高度适配
            drawHeight = ctx.canvas.height;
            drawWidth = drawHeight * imgAspect;
            drawX = (ctx.canvas.width - drawWidth) / 2;
            drawY = 0;
        } else {
            // 图片更高，按宽度适配
            drawWidth = ctx.canvas.width;
            drawHeight = drawWidth / imgAspect;
            drawX = 0;
            drawY = (ctx.canvas.height - drawHeight) / 2;
        }
        
        // 添加半透明遮罩，让方块更清晰
        ctx.globalAlpha = 0.6;
        ctx.drawImage(backgroundImage, drawX, drawY, drawWidth, drawHeight);
        ctx.globalAlpha = 1.0;
    }
    
    // 绘制荧光尾巴射线效果（先绘制尾巴，后绘制方块，产生层次感）
    if (currentPiece && trailHistory.length > 0) {
        drawTrailEffect(ctx);
    }
    
    // 绘制已放置的方块（玻璃质感）
    for (let y = 0; y < ROWS; y++) {
        for (let x = 0; x < COLS; x++) {
            if (board[y][x]) {
                drawBlock(ctx, x, y, board[y][x], 0.65);
            }
        }
    }
    
    // 绘制硬降预览位置（透明轮廓）
    if (currentPiece) {
        drawGhostPiece(ctx);
    }
    
    // 绘制当前下落的方块（更明显的玻璃效果）
    if (currentPiece) {
        for (let y = 0; y < currentPiece.shape.length; y++) {
            for (let x = 0; x < currentPiece.shape[y].length; x++) {
                if (currentPiece.shape[y][x]) {
                    drawBlock(ctx, 
                        currentPiece.x + x, 
                        currentPiece.y + y, 
                        currentPiece.color,
                        0.7
                    );
                }
            }
        }
    }
}

// 计算硬降位置
function getGhostPiecePosition() {
    if (!currentPiece) return null;
    
    let ghostY = currentPiece.y;
    const tempPiece = {
        x: currentPiece.x,
        y: ghostY,
        shape: currentPiece.shape
    };
    
    // 模拟下落，找到最终位置
    while (isValidMove({ ...currentPiece, y: ghostY + 1 }, 0, 0)) {
        ghostY++;
    }
    
    return {
        x: currentPiece.x,
        y: ghostY,
        shape: currentPiece.shape,
        color: currentPiece.color
    };
}

// 绘制硬降预览（透明轮廓）
function drawGhostPiece(ctx) {
    const ghost = getGhostPiecePosition();
    if (!ghost) return;
    
    // 如果预览位置和当前位置相同，不绘制
    if (ghost.y === currentPiece.y) return;
    
    ctx.save();
    
    // 绘制透明轮廓
    for (let y = 0; y < ghost.shape.length; y++) {
        for (let x = 0; x < ghost.shape[y].length; x++) {
            if (ghost.shape[y][x]) {
                const px = (ghost.x + x) * BLOCK_SIZE;
                const py = (ghost.y + y) * BLOCK_SIZE;
                const radius = 5;
                
                // 只绘制轮廓，不填充
                ctx.strokeStyle = 'rgba(255, 255, 255, 0.3)';
                ctx.lineWidth = 2;
                ctx.setLineDash([4, 4]); // 虚线样式
                
                ctx.beginPath();
                ctx.moveTo(px + radius, py);
                ctx.lineTo(px + BLOCK_SIZE - radius, py);
                ctx.quadraticCurveTo(px + BLOCK_SIZE, py, px + BLOCK_SIZE, py + radius);
                ctx.lineTo(px + BLOCK_SIZE, py + BLOCK_SIZE - radius);
                ctx.quadraticCurveTo(px + BLOCK_SIZE, py + BLOCK_SIZE, px + BLOCK_SIZE - radius, py + BLOCK_SIZE);
                ctx.lineTo(px + radius, py + BLOCK_SIZE);
                ctx.quadraticCurveTo(px, py + BLOCK_SIZE, px, py + BLOCK_SIZE - radius);
                ctx.lineTo(px, py + radius);
                ctx.quadraticCurveTo(px, py, px + radius, py);
                ctx.closePath();
                ctx.stroke();
            }
        }
    }
    
    ctx.restore();
}

// 绘制下一个方块预览 - 玻璃质感（直接在预览画布上绘制）
function drawNextPiece(ctx) {
    ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height);
    
    if (nextPiece) {
        const shape = nextPiece.shape;
        const previewBlockSize = 25; // 预览区域的小方块尺寸
        const offsetX = (ctx.canvas.width - shape[0].length * previewBlockSize) / 2;
        const offsetY = (ctx.canvas.height - shape.length * previewBlockSize) / 2;
        
        const color = hexToRgb(nextPiece.color);
        const radius = 4;
        
        for (let y = 0; y < shape.length; y++) {
            for (let x = 0; x < shape[y].length; x++) {
                if (shape[y][x]) {
                    const px = offsetX + x * previewBlockSize;
                    const py = offsetY + y * previewBlockSize;
                    
                    ctx.save();
                    
                    // 绘制圆角矩形路径
                    ctx.beginPath();
                    ctx.moveTo(px + radius, py);
                    ctx.lineTo(px + previewBlockSize - radius, py);
                    ctx.quadraticCurveTo(px + previewBlockSize, py, px + previewBlockSize, py + radius);
                    ctx.lineTo(px + previewBlockSize, py + previewBlockSize - radius);
                    ctx.quadraticCurveTo(px + previewBlockSize, py + previewBlockSize, px + previewBlockSize - radius, py + previewBlockSize);
                    ctx.lineTo(px + radius, py + previewBlockSize);
                    ctx.quadraticCurveTo(px, py + previewBlockSize, px, py + previewBlockSize - radius);
                    ctx.lineTo(px, py + radius);
                    ctx.quadraticCurveTo(px, py, px + radius, py);
                    ctx.closePath();
                    
                    // 玻璃质感
                    ctx.fillStyle = `rgba(${color.r}, ${color.g}, ${color.b}, 0.75)`;
                    ctx.fill();
                    
                    // 玻璃边框
                    ctx.strokeStyle = 'rgba(255, 255, 255, 0.6)';
                    ctx.lineWidth = 1.5;
                    ctx.stroke();
                    
                    // 玻璃高光
                    const highlightGradient = ctx.createLinearGradient(px, py, px + previewBlockSize, py + previewBlockSize * 0.6);
                    highlightGradient.addColorStop(0, 'rgba(255, 255, 255, 0.5)');
                    highlightGradient.addColorStop(1, 'rgba(255, 255, 255, 0)');
                    ctx.fillStyle = highlightGradient;
                    ctx.fill();
                    
                    ctx.restore();
                }
            }
        }
    }
}

// 碰撞检测
function isValidMove(piece, dx, dy, rotatedShape = null) {
    const shape = rotatedShape || piece.shape;
    const newX = piece.x + dx;
    const newY = piece.y + dy;
    
    for (let y = 0; y < shape.length; y++) {
        for (let x = 0; x < shape[y].length; x++) {
            if (shape[y][x]) {
                const boardX = newX + x;
                const boardY = newY + y;
                
                // 检查边界
                if (boardX < 0 || boardX >= COLS || boardY >= ROWS) {
                    return false;
                }
                
                // 检查与已放置方块的碰撞
                if (boardY >= 0 && board[boardY][boardX]) {
                    return false;
                }
            }
        }
    }
    return true;
}

// 旋转方块
function rotatePiece(piece) {
    const rotated = piece.shape[0].map((_, i) =>
        piece.shape.map(row => row[i]).reverse()
    );
    return rotated;
}

// 放置方块到游戏板
function placePiece() {
    // 播放触底音效
    if (landSound) {
        playSound(landSound);
    }
    
    for (let y = 0; y < currentPiece.shape.length; y++) {
        for (let x = 0; x < currentPiece.shape[y].length; x++) {
            if (currentPiece.shape[y][x]) {
                const boardY = currentPiece.y + y;
                const boardX = currentPiece.x + x;
                if (boardY >= 0 && boardY < ROWS) {
                    board[boardY][boardX] = currentPiece.color;
                }
            }
        }
    }
    
    // 放置后检查是否触到顶部
    if (checkGameOver()) {
        endGame();
        return;
    }
}

// 清除完整的行
function clearLines() {
    let linesCleared = 0;
    
    for (let y = ROWS - 1; y >= 0; y--) {
        if (board[y].every(cell => cell !== 0)) {
            board.splice(y, 1);
            board.unshift(Array(COLS).fill(0));
            linesCleared++;
            y++; // 重新检查当前行
        }
    }
    
    if (linesCleared > 0) {
        // 播放消除行音效
        if (clearSound) {
            playSound(clearSound);
        }
        
        lines += linesCleared;
        
        // 计算分数
        const points = [0, 40, 100, 300, 1200];
        score += points[linesCleared] * level;
        
        // 更新等级（每10行升一级）
        level = Math.floor(lines / 10) + 1;
        
        updateUI();
    }
}

// 更新UI
function updateUI() {
    document.getElementById('score').textContent = score;
    document.getElementById('level').textContent = level;
    document.getElementById('lines').textContent = lines;
}

// 游戏结束检查 - 检查方块是否触到顶部
function checkGameOver() {
    if (!currentPiece) return false;
    
    // 检查方块是否有任何部分在顶部（y < 0 或 y == 0且顶部有方块）
    for (let y = 0; y < currentPiece.shape.length; y++) {
        for (let x = 0; x < currentPiece.shape[y].length; x++) {
            if (currentPiece.shape[y][x]) {
                const boardY = currentPiece.y + y;
                // 如果方块位置小于0（在顶部之上）或者在顶部行（y=0）且无法移动
                if (boardY < 0) {
                    return true;
                }
                // 如果方块在顶部行且有已放置的方块阻挡
                if (boardY === 0 && board[0] && board[0][currentPiece.x + x]) {
                    return true;
                }
            }
        }
    }
    
    // 检查顶部行是否有已放置的方块
    if (board[0] && board[0].some(cell => cell !== 0)) {
        return true;
    }
    
    return false;
}

// 硬降（立即下落到底部）
function hardDrop() {
    while (isValidMove(currentPiece, 0, 1)) {
        currentPiece.y++;
    }
    placePiece();
    // placePiece中已经检查了游戏结束
    
    if (gameRunning) {
        clearLines();
        
        // 计算硬降分数
        score += 2;
        
        currentPiece = nextPiece;
        nextPiece = createPiece();
        
        // 再次检查新方块是否立即触顶
        if (checkGameOver()) {
            endGame();
        }
        
        updateUI();
        drawNextPiece(document.getElementById('nextCanvas').getContext('2d'));
    }
}

// 移动方块
function movePiece(dx, dy) {
    if (isValidMove(currentPiece, dx, dy)) {
        // 记录移动前的位置用于生成荧光尾巴特效
        if (lastPiecePosition && (dx !== 0 || dy !== 0)) {
            // 添加历史位置到尾巴数组（使用数组map而非JSON序列化）
            trailHistory.push({
                x: lastPiecePosition.x,
                y: lastPiecePosition.y,
                shape: lastPiecePosition.shape.map(row => [...row]),
                color: lastPiecePosition.color
            });
            
            // 限制历史点数量，避免性能问题
            if (trailHistory.length > 8) {
                trailHistory.shift();
            }
        }
        
        // 播放移动音效（仅左右移动，不包括下落）
        if (dx !== 0 && moveSound) {
            playSound(moveSound);
        }
        
        // 更新位置（使用浅拷贝而非JSON序列化）
        lastPiecePosition = {
            x: currentPiece.x,
            y: currentPiece.y,
            shape: currentPiece.shape.map(row => [...row]),
            color: currentPiece.color
        };
        
        currentPiece.x += dx;
        currentPiece.y += dy;
        return true;
    }
    return false;
}

// 旋转当前方块
function rotateCurrentPiece() {
    const rotated = rotatePiece(currentPiece);
    if (isValidMove(currentPiece, 0, 0, rotated)) {
        // 播放旋转音效
        if (rotateSound) {
            playSound(rotateSound);
        }
        
        // 记录旋转前的位置用于荧光尾巴特效
        if (lastPiecePosition) {
            trailHistory.push({
                x: currentPiece.x,
                y: currentPiece.y,
                shape: currentPiece.shape.map(row => [...row]),
                color: currentPiece.color
            });
            
            if (trailHistory.length > 8) {
                trailHistory.shift();
            }
        }
        
        lastPiecePosition = {
            x: currentPiece.x,
            y: currentPiece.y,
            shape: currentPiece.shape.map(row => [...row]),
            color: currentPiece.color
        };
        
        currentPiece.shape = rotated;
        return true;
    }
    return false;
}

// 方块下落
function dropPiece() {
    if (!movePiece(0, 1)) {
        placePiece();
        // placePiece中已经检查了游戏结束
        
        if (gameRunning) {
            clearLines();
            
            // 清空荧光尾巴历史，准备新的方块
            trailHistory = [];
            lastPiecePosition = null;
            
            currentPiece = nextPiece;
            nextPiece = createPiece();
            
            // 再次检查新方块是否立即触顶
            if (checkGameOver()) {
                endGame();
            }
            
            updateUI();
            drawNextPiece(document.getElementById('nextCanvas').getContext('2d'));
        }
    }
}

// 游戏循环
function gameLoop(time = 0) {
    if (!gameRunning || gamePaused) {
        requestAnimationFrame(gameLoop);
        return;
    }
    
    const deltaTime = time - lastTime;
    lastTime = time;
    
    dropTime += deltaTime;
    
    // 根据难度和等级调整下落速度
    let baseSpeed = 1000;
    switch(gameDifficulty) {
        case 'easy':
            baseSpeed = 1500; // 消极：更慢
            break;
        case 'medium':
            baseSpeed = 1000; // 中等：标准
            break;
        case 'hard':
            baseSpeed = 600; // 疯狂：更快
            break;
    }
    const dropInterval = Math.max(100, baseSpeed - (level - 1) * (baseSpeed / 10));
    
    if (dropTime > dropInterval) {
        dropPiece();
        dropTime = 0;
    }
    
    const ctx = document.getElementById('gameCanvas').getContext('2d');
    drawBoard(ctx);
    
    requestAnimationFrame(gameLoop);
}

// 开始游戏
function startGame(difficulty = 'medium') {
    gameDifficulty = difficulty;
    gameStarted = true;
    
    // 隐藏开始界面
    document.getElementById('startMenu').classList.add('hidden');
    document.querySelector('.game-content').classList.remove('hidden');
    
    initBoard();
    score = 0;
    level = 1;
    lines = 0;
    gameRunning = true;
    gamePaused = false;
    dropTime = 0;
    lastTime = 0;
    trailHistory = [];
    lastPiecePosition = null;
    
    // 重置音乐到第一首
    currentMusicIndex = 0;
    if (backgroundMusicList.length > 0) {
        backgroundMusic = backgroundMusicList[0];
    }
    
    currentPiece = createPiece();
    nextPiece = createPiece();
    
    document.getElementById('gameOver').classList.add('hidden');
    document.getElementById('gamePaused').classList.add('hidden');
    
    // 播放背景音乐（尝试多次，因为可能需要用户交互）
    if (backgroundMusic && !musicMuted) {
        const tryPlayMusic = () => {
            if (backgroundMusic && gameRunning) {
                backgroundMusic.play().then(() => {
                    console.log('背景音乐开始播放');
                }).catch(e => {
                    // 如果是因为用户交互策略，在第一次用户操作时再试
                    console.log('背景音乐需要用户交互后才能播放');
                });
            }
        };
        
        // 立即尝试播放
        tryPlayMusic();
        
        // 监听用户第一次按键，再次尝试播放
        const onceKeyHandler = () => {
            tryPlayMusic();
            document.removeEventListener('keydown', onceKeyHandler);
        };
        document.addEventListener('keydown', onceKeyHandler, { once: true });
    }
    
    updateUI();
    
    const nextCtx = document.getElementById('nextCanvas').getContext('2d');
    drawNextPiece(nextCtx);
    
    requestAnimationFrame(gameLoop);
}

// 播放音效（短音效，每次重新播放）
function playSound(sound) {
    if (!sound) return;
    
    try {
        // 创建新的音频对象以避免冲突（如果音效很短）
        const soundClone = sound.cloneNode();
        soundClone.volume = sound.volume;
        soundClone.currentTime = 0;
        soundClone.play().catch(e => {
            // 忽略播放错误（可能是用户未交互或浏览器策略限制）
            // console.log('音效播放失败:', e);
        });
    } catch (e) {
        // 如果clone失败，尝试直接播放
        if (sound.readyState >= 2) {
            sound.currentTime = 0;
            sound.play().catch(err => {
                // console.log('音效播放失败:', err);
            });
        }
    }
}

// 加载所有音频
function loadAudio() {
    // 加载背景音乐列表 - 只尝试加载最多3个文件
    for (let i = 1; i <= 10; i++) {
        const music = new Audio(`background${i}.mp3`);
        music.loop = false; // 不循环，由我们手动控制
        music.volume = 0.01; // 背景音乐音量1%（iPhone最大音量时合适）
        music.preload = 'none'; // 改为需要时再加载，不预加载
        
        music.onerror = function(e) {
            // 文件不存在，停止加载
            console.log(`背景音乐 background${i}.mp3 不存在`);
        };
        
        music.onended = function() {
            // 当前音乐播放完毕，播放下一首
            if (!musicMuted && gameRunning && !gamePaused) {
                playNextMusic();
            }
        };
        
        backgroundMusicList.push(music);
    }
    
    // 初始化第一首音乐
    if (backgroundMusicList.length > 0) {
        backgroundMusic = backgroundMusicList[0];
        currentMusicIndex = 0;
        console.log('背景音乐列表加载完成，共' + backgroundMusicList.length + '首');
    }
    
    // 加载移动音效
    moveSound = new Audio('move.mp3');
    moveSound.volume = 0.005;
    moveSound.preload = 'none';
    moveSound.onerror = function(e) {
        console.error('移动音效加载失败:', e);
        moveSound = null;
    };
    
    // 加载旋转音效
    rotateSound = new Audio('rotate.mp3');
    rotateSound.volume = 0.005;
    rotateSound.preload = 'none';
    rotateSound.onerror = function(e) {
        console.error('旋转音效加载失败:', e);
        rotateSound = null;
    };
    
    // 加载触底音效
    landSound = new Audio('land.mp3');
    landSound.volume = 0.005;
    landSound.preload = 'none';
    landSound.onerror = function(e) {
        console.error('触底音效加载失败:', e);
        landSound = null;
    };
    
    // 加载消除行音效
    clearSound = new Audio('clear.mp3');
    clearSound.volume = 0.005;
    clearSound.preload = 'none';
    clearSound.onerror = function(e) {
        console.error('消除行音效加载失败:', e);
        clearSound = null;
    };
    
    // 加载游戏结束音效
    failSound = new Audio('fail.mp3');
    failSound.volume = 0.01;
    failSound.preload = 'none';
    failSound.onerror = function(e) {
        console.error('游戏结束音效加载失败:', e);
        failSound = null;
    };
}

// 加载背景图片
function loadBackgroundImage() {
    const img = new Image();
    img.onload = function() {
        backgroundImage = img;
        // 如果游戏未开始，也设置开始界面背景
        if (!gameStarted) {
            setStartMenuBackground(img);
        }
    };
    img.onerror = function() {
        console.log('背景图片加载失败，将使用默认背景');
        backgroundImage = null;
    };
    // 尝试加载背景图片（用户需要将图片命名为 background.jpg 并放在项目目录）
    img.src = 'background.jpg';
}

// 设置开始界面背景
function setStartMenuBackground(img) {
    const startMenu = document.getElementById('startMenu');
    if (startMenu) {
        // 计算背景图片的适配
        const imgAspect = img.width / img.height;
        const menuAspect = startMenu.offsetWidth / startMenu.offsetHeight;
        
        // 设置为背景图片
        startMenu.style.backgroundImage = `url('background.jpg')`;
        startMenu.style.backgroundSize = 'cover';
        startMenu.style.backgroundPosition = 'center';
        startMenu.style.backgroundRepeat = 'no-repeat';
    }
}

// 结束游戏
function endGame() {
    gameRunning = false;
    
    // 停止背景音乐
    if (backgroundMusic) {
        backgroundMusic.pause();
        backgroundMusic.currentTime = 0;
    }
    
    // 播放游戏结束音效
    if (failSound && !musicMuted) {
        playSound(failSound);
    }
    
    document.getElementById('finalScore').textContent = score;
    document.getElementById('gameOver').classList.remove('hidden');
}

// 播放下一首音乐
function playNextMusic() {
    if (backgroundMusicList.length === 0) return;
    
    // 停止当前音乐
    if (backgroundMusic) {
        backgroundMusic.pause();
        backgroundMusic.currentTime = 0;
    }
    
    // 切换到下一首
    currentMusicIndex = (currentMusicIndex + 1) % backgroundMusicList.length;
    backgroundMusic = backgroundMusicList[currentMusicIndex];
    
    // 播放下一首
    if (gameRunning && !gamePaused && !musicMuted) {
        backgroundMusic.play().catch(e => {
            console.log('背景音乐播放失败:', e);
        });
    }
}

// 切换背景音乐（按E键调用）
function switchMusic() {
    if (backgroundMusicList.length === 0) return;
    
    // 停止当前音乐
    if (backgroundMusic) {
        backgroundMusic.pause();
        backgroundMusic.currentTime = 0;
    }
    
    // 切换到下一首
    currentMusicIndex = (currentMusicIndex + 1) % backgroundMusicList.length;
    backgroundMusic = backgroundMusicList[currentMusicIndex];
    
    // 如果游戏正在进行且未静音，播放
    if (gameRunning && !gamePaused && !musicMuted) {
        backgroundMusic.play().catch(e => {
            console.log('背景音乐播放失败:', e);
        });
    }
}

// 暂停/继续游戏
function togglePause() {
    if (!gameRunning) return;
    
    gamePaused = !gamePaused;
    if (gamePaused) {
        // 暂停背景音乐（如果未被静音）
        if (backgroundMusic && !backgroundMusic.paused && !musicMuted) {
            backgroundMusic.pause();
        }
        document.getElementById('gamePaused').classList.remove('hidden');
    } else {
        // 继续播放背景音乐（如果未被静音）
        if (backgroundMusic && !musicMuted) {
            backgroundMusic.play().catch(e => {
                // console.log('背景音乐播放失败:', e);
            });
        }
        document.getElementById('gamePaused').classList.add('hidden');
        lastTime = performance.now();
    }
}

// 控制音乐播放/停止
function toggleMusic() {
    if (!backgroundMusic) return;
    
    musicMuted = !musicMuted;
    if (musicMuted) {
        // 停止音乐
        backgroundMusic.pause();
    } else {
        // 播放音乐
        if (gameRunning && !gamePaused) {
            backgroundMusic.play().catch(e => {
                // console.log('背景音乐播放失败:', e);
            });
        }
    }
}

// 回到开始界面
function goBackToStart() {
    // 停止游戏
    gameRunning = false;
    gamePaused = false;
    
    // 停止音乐
    if (backgroundMusic) {
        backgroundMusic.pause();
        backgroundMusic.currentTime = 0;
    }
    
    // 显示开始界面
    document.getElementById('startMenu').classList.remove('hidden');
    document.querySelector('.game-content').classList.add('hidden');
    document.getElementById('gameOver').classList.add('hidden');
    document.getElementById('gamePaused').classList.add('hidden');
    
    gameStarted = false;
    musicMuted = false; // 重置音乐状态
}

// 键盘控制
document.addEventListener('keydown', (e) => {
    // 检查是否需要处理全局快捷键（游戏进行中或暂停时都可用）
    if (e.key === 'q' || e.key === 'Q') {
        // Q键回到开始界面
        goBackToStart();
        return;
    }
    
    if (e.key === 'm' || e.key === 'M') {
        // M键控制音乐播放/停止
        toggleMusic();
        return;
    }
    
    if (e.key === 'e' || e.key === 'E') {
        // E键切换背景音乐
        if (gameRunning && !gamePaused) {
            switchMusic();
        }
        return;
    }
    
    if (!gameRunning || gamePaused) {
        if (e.key === 'p' || e.key === 'P') {
            togglePause();
        }
        return;
    }
    
    switch(e.key) {
        case 'a':
        case 'A':
            movePiece(-1, 0);
            break;
        case 'd':
        case 'D':
            movePiece(1, 0);
            break;
        case 's':
        case 'S':
            if (movePiece(0, 1)) {
                score += 1;
                updateUI();
            }
            break;
        case 'w':
        case 'W':
            rotateCurrentPiece();
            break;
        case ' ':
            e.preventDefault();
            hardDrop();
            break;
        case 'p':
        case 'P':
            togglePause();
            break;
    }
});

// 重新开始按钮
document.getElementById('restartBtn').addEventListener('click', () => {
    // 显示开始界面
    document.getElementById('startMenu').classList.remove('hidden');
    document.querySelector('.game-content').classList.add('hidden');
    gameStarted = false;
    gameRunning = false;
});

// 难度按钮事件
document.addEventListener('DOMContentLoaded', () => {
    const easyBtn = document.getElementById('easyBtn');
    const mediumBtn = document.getElementById('mediumBtn');
    const hardBtn = document.getElementById('hardBtn');
    
    if (easyBtn) easyBtn.addEventListener('click', () => startGame('easy'));
    if (mediumBtn) mediumBtn.addEventListener('click', () => startGame('medium'));
    if (hardBtn) hardBtn.addEventListener('click', () => startGame('hard'));
});

// 初始化
window.addEventListener('load', () => {
    loadBackgroundImage();
    loadAudio(); // 加载音频文件
    // 不自动开始游戏，显示开始界面
    document.querySelector('.game-content').classList.add('hidden');
});
